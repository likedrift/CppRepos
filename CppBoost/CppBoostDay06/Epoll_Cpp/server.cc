#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/epoll.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

void test01()
{
    int listenfd = ::socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == listenfd)
    {
        perror("socket");
        exit(-1);
    }

    int opt = 1;
    // SOL_SOCKET是一个用于指定套接字选项操作时的级别
    int ret = setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (-1 == ret)
    {
        perror("setsockopt");
        close(listenfd);
        exit(-1);
    }

    // 端口复用
    ret = setsockopt(listenfd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));
    if (-1 == ret)
    {
        perror("setsockopt");
        close(listenfd);
        exit(-1);
    }

    // 网络地址需要采用网络字节序存储(大端模式)
    struct sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8888);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    socklen_t length = sizeof(serverAddr);

    // bind
    if (::bind(listenfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        perror("bind");
        close(listenfd);
        exit(-1);
    }

    // listen
    if (::listen(listenfd, 128) < 0)
    {
        perror("listen");
        close(listenfd);
        exit(-1);
    }

    cout << "server is listening..." << endl;

    // 创建epoll实例
    int efd = ::epoll_create1(0);
    struct epoll_event ev;
    ev.events = EPOLLIN | EPOLLOUT;
    ev.data.fd = listenfd;

    // epoll要进行监听操作：对listenfd的读事件进行监听
    ret = ::epoll_ctl(efd, EPOLL_CTL_ADD, listenfd, &ev);
    if (-1 == ret)
    {
        perror("epoll_ctl");
        close(listenfd);
        close(efd);
        exit(-1);
    }

    struct epoll_event *evtList =
        (struct epoll_event *)malloc(1024 * sizeof(struct epoll_event));

    // 事件循环
    while (1)
    {
        // epoll_wait的行为：
        // int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);
        int nready = ::epoll_wait(efd, evtList, 1024, 3000);
        if (-1 == nready && errno == EINTR)
        {
            continue;
        }
        else if (-1 == nready)
        {
            perror("epoll_wait");
            exit(-1);
        }
        else if (0 == nready)
        {
            cout << ">> epoll_wait timeout!" << endl;
        }
        else
        {
            // 遍历struct epoll_event数组
            // 检查每一个epoll_event到底发生了什么事件

            for (int idx = 0; idx < nready; ++idx)
            {
                // listenfd就绪，就是新连接来了
                if ((evtList[idx].data.fd == listenfd) &&
                    (evtList[idx].events & EPOLLIN))
                {
                    int peerfd = ::accept(listenfd, nullptr, nullptr);

                    // 新连接添加到epoll的监听实例中
                    struct epoll_event ev;
                    ev.events = EPOLLIN | EPOLLOUT | EPOLLERR;
                    ev.data.fd = peerfd;
                    // 将fd添加进epfd中进监听其event类型的事件的发生
                    ret = ::epoll_ctl(efd, EPOLL_CTL_ADD, peerfd, &ev);
                    if (-1 == ret)
                    {
                        perror("epoll_ctl");
                        continue;
                    }

                    // 新连接到来之后的处理
                    cout << ">> conn has connected, fd: " << peerfd << endl;
                }
                else
                { // evtList[idx].data.fd == !listenfd
                    // 已经建立好的连接发送数据过来了
                    // 发生读事件
                    char buf[128] = {0};
                    if (evtList[idx].events & EPOLLIN)
                    {
                        int fd = evtList[idx].data.fd;
                        // ret 为接收到的字节数
                        ret = ::recv(fd, buf, sizeof(buf), 0);

                        if (ret > 0)
                        {
                            cout << ">>> recv msg " << ret << " bytes,content:" << buf << endl;

                            ret = send(fd, buf, strlen(buf), 0);
                            cout << ">>> send " << ret << " bytes" << endl;
                        }
                        else if (0 == ret)
                        {

                            // When a stream socket peer has performed an orderly shutdown,
                            // the return value will be 0 (the traditional "end-of-file" return)
                            cout << "conn has closed" << endl;
                            // 需要从epoll监听实例中删除掉，因为连接断开了
                            struct epoll_event ev;
                            ev.data.fd = fd;
                            ret = ::epoll_ctl(efd, EPOLL_CTL_DEL, fd, &ev);
                            if (-1 == ret)
                            {
                                perror("epoll_ctl");
                            }
                        }
                    }
                }
            }
        }
    }
    close(listenfd);
    delete[] evtList;
}

int main(void)
{
    test01();
    return 0;
}