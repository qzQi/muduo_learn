
#include<string.h>
#include<stdlib.h>
#include<errno.h>
#include<stdio.h>

#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/epoll.h>

#include<iostream>
#include<vector>


typedef std::vector<struct epoll_event>EventList;
// epoll不需要频繁的向内核拷贝数据（我们所关心的数据），

#define ERR_EXIT(m)\
    do \
    {\
        perror(m); \
        exit(EXIT_FAILURE);  \
    }while(0)

int main()
{
    signal(SIGPIPE,SIG_IGN);
    signal(SIGCHLD,SIG_IGN);

    int idlefd=open("/dev/null",O_RDONLY|O_CLOEXEC);
    int listenfd;

    if((listenfd=socket(PF_INET,SOCK_STREAM|SOCK_NONBLOCK|SOCK_CLOEXEC))<0)
        ERR_EXIT("socket");

        struct sockaddr_in servaddr;
        memset(&servaddr,0,sizeof(servaddr));
        servaddr.sin_family=AF_INET;
        servaddr.sin_addr.s_addr=htonl(INADDR_ANY);//监听所有的
        servaddr.sin_port = htons(5188);//要明确我们的服务器开放这个端口没有

    int on = 1;
	if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
		ERR_EXIT("setsockopt");

	if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
		ERR_EXIT("bind");
	if (listen(listenfd, SOMAXCONN) < 0)
		ERR_EXIT("listen");

    std::vector<int>clients;

    int epollfd;
    epollfd=epoll_create1(EPOLL_CLOEXEC);
    struct epoll_event event;
    event.data.fd=listenfd;
    event.events=EPOLLIN;//EPOLLIN|EPOLLET
    epoll_ctl(epollfd,EPOLL_CTL_ADD,listenfd,&event);

    EventList events(16);
    struct sockaddr_in peeraddr;
    socklen_t peerlen;
    int connfd;

    int nready=0;
    while(1)
    {
        // 通过events数组内核把结果传递给我们，一个结果参数？
        nready=epoll_wait(epollfd,events.data(),events.size(),-1);
        if (nready == -1)
		{
			if (errno == EINTR)
				continue;
			
			ERR_EXIT("epoll_wait");
		}

    }



}

