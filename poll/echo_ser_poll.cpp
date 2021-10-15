#include<unistd.h>
#include<sys/socket.h>
#include<poll.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<signal.h>
#include<sys/wait.h>
#include<fcntl.h>

#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>

#include<vector>
#include<iostream>

typedef std::vector<struct pollfd> PollFdList;

#define ERR_EXIT(m)\
    do \
    { \
        perror(m); \
        exit(EXIT_FAILURE);\
    }while(0)

int main()
{
    signal(SIGPIPE,SIG_IGN);
    signal(SIGCHLD,SIG_IGN);

    int idlefd=open("/dev/null",O_RDONLY|O_CLOEXEC);
    // 防止fd耗尽，无法ac

    int listenfd;
    if((listenfd=socket(PF_INET,SOCK_STREAM|SOCK_NONBLOCK|SOCK_CLOEXEC,IPPROTO_TCP))<0)
        ERR_EXIT("socket");

    // bind addr
    struct sockaddr_in servaddr;
    memset(&servaddr,0,sizeof(servaddr));
    servaddr.sin_family=AF_INET;
    servaddr.sin_port = htons(5188);
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

    int on = 1;
	if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
		ERR_EXIT("setsockopt");

	if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
		ERR_EXIT("bind");
	if (listen(listenfd, SOMAXCONN) < 0)
		ERR_EXIT("listen");

    struct pollfd pfd;
    pfd.fd=listenfd;
    pfd.events=POLLIN;

    PollFdList pollfds;
    pollfds.push_back(pfd);

    int nready=0;//select与poll返回的是ready的数目，但是我们仍然不得不遍历它

    struct sockaddr_in peeraddr;
	socklen_t peerlen;
	int connfd;

    while(true)
    {
        nready=poll(pollfds.data(),pollfds.size(),-1);
        if (nready == -1)
		{
			if (errno == EINTR)
				continue;
			
			ERR_EXIT("poll");
		}

        if (nready == 0)	// nothing happended
			continue;
		
		if (pollfds[0].revents & POLLIN)
		{
			peerlen = sizeof(peeraddr);
			connfd = accept4(listenfd, (struct sockaddr*)&peeraddr,
						&peerlen, SOCK_NONBLOCK | SOCK_CLOEXEC);



			if (connfd == -1)
			{
				if (errno == EMFILE)
				{
					close(idlefd);
					idlefd = accept(listenfd, NULL, NULL);
					close(idlefd);
					idlefd = open("/dev/null", O_RDONLY | O_CLOEXEC);
					continue;
				}
				else
					ERR_EXIT("accept4");
			}

			pfd.fd = connfd;
			pfd.events = POLLIN;
			pfd.revents = 0;
			pollfds.push_back(pfd);
			--nready;

			// 连接成功
			std::cout<<"ip="<<inet_ntoa(peeraddr.sin_addr)<<
				" port="<<ntohs(peeraddr.sin_port)<<std::endl;
			if (nready == 0)
				continue;
		}

        for(auto it=pollfds.begin()+1;nready>0&&it!=pollfds.end();++it)
        {
            if(it->revents&&POLLIN)
            {
                --nready;
					connfd = it->fd;

                    // 由于我们使用的non_block这里的缓冲区没有进行处理
					char buf[1024] = {0};
					int ret = read(connfd, buf, 1024);
					if (ret == -1)
						ERR_EXIT("read");
					if (ret == 0)
					{
						std::cout<<"client close"<<std::endl;
						it = pollfds.erase(it);
						--it;

						close(connfd);
						continue;
					}

					std::cout<<buf;
					write(connfd, buf, strlen(buf));
            }
        }


    }
    return 0;

}