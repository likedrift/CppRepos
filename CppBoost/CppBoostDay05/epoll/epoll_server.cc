#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/epoll.h>
#include <string.h>

#define SERV_PORT 8888
#define OPEN_MAX 5000

int main(){

    /* 服务端绑定内容 */
    
    // 1. 创建套接字
    int listenfd;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == listenfd){
        perror("socket");
        exit(-1);
    }

    // 2. 地址复用
    int opt = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // 3. 端口复用
    int opt2 = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEPORT, &opt2, sizeof(opt2));

    struct sockaddr_in serv_addr, clie_addr;
    socklen_t clie_addr_len;
    
    // 4. 绑定ip和port
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    int ret;
    ret = bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));
    if(-1 == ret){
        perror("bind");
        close(listenfd);
        exit(-1);
    }

    // 5. 服务器监听
    // 让listenfd设置为监听状态，开始等待来自客户端的请求
    // 128制定了未完成连接队列的最大长度，即最多允许有128个
    // 客户端的连接请求在服务器端尚未被accept()处理的情况下排队等待
    // 这个队列用于存放那些已经完成了 TCP 三次握手
    // 建立了半连接（即服务器端已经收到客户端的 SYN 包并发送了 SYN+ACK 应答
    // 但还没有被 accept() 函数正式接受并分配新的套接字）的客户端连接。
    ret = listen(listenfd, 128);
    if(-1 == ret){
        perror("listen");
        close(listenfd);
        exit(-1);
    }

    printf("server is listening...\n");

    // 6. epoll类型 IO多路复用
    int epfd = epoll_create(OPEN_MAX);
    if(-1 == epfd){
        perror("epoll_create");
        close(listenfd);
        exit(-1);
    }

    struct epoll_event evt, ep[OPEN_MAX];
    evt.events = EPOLLIN;
    evt.data.fd = listenfd;

    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &evt);
    if(-1 == ret){
        perror("epoll_ctl");
        close(listenfd);
        exit(-1);
    }

    int nready, nByte, i, j;
    char buf[BUFSIZ], str[BUFSIZ];
    int connfd, sockfd;
    while(1){
        // 6.1 使用epoll_wait负责监听，如果返回值大于0
        // 表示有满足条件的连接被监听到
        nready = epoll_wait(epfd, ep, OPEN_MAX, -1);
        if(nready < 0){
            perror("epoll_wait");
            close(listenfd);
            exit(-1);
        }

        // 7. 遍历nready
        for(i = 0; i < nready; ++i){
            // 7.1 异常处理
            if(!(ep[i].events & EPOLLIN)){
                continue;
            }

            // 7.2 如果监听到的是listenfd，表示有新的请求进来
            if(ep[i].data.fd == listenfd){
                clie_addr_len = sizeof(clie_addr);
                // 8. 有新的连接，那么accept肯定会有返回值
                // listenfd是已经通过listen()设置的套接字描述符
                // accept的第二个参数用于存储已连接的客户端信息
                // 用于指定指向addr参数所指向的地址结构体的大小
                connfd = accept(listenfd, (struct sockaddr *)&clie_addr, &clie_addr_len);
                if(-1 == connfd){
                    perror("accpet");
                    close(listenfd);
                    exit(-1);
                }

                printf("receive from %s from port %d\n", 
                       inet_ntop(AF_INET, &clie_addr.sin_addr, str, sizeof(str)),
                       ntohs(clie_addr.sin_port));
                
                // 将connfd放在红黑树上继续监听
                // 类似于select中放在client数组中继续监听一样(?)
                evt.events = EPOLLIN;
                evt.data.fd = connfd;
                epoll_ctl(epfd, EPOLL_CTL_ADD, connfd, &evt);

            }
            // 7.3 不是listenfd就绪，那就说明是connfd就绪
            // 即不是连接建立事件而是信息传递事件
            // 就表明是老的连接上有数据可读
            // 肯定是客户端有数据发送过来，所以就可以使用read/write接收
            else{
                sockfd = ep[i].data.fd;
                nByte = read(sockfd, buf, sizeof(buf));
                //表明数据读完了（对应的缓冲区中没有数据了）
                //也就是表明连接马上要断开了
                if(nByte == 0){
                    ret = epoll_ctl(epfd, EPOLL_CTL_DEL, sockfd, NULL);
                    if(-1 == ret){
                        perror("epoll_ctl");
                    }
                    close(sockfd);
                    printf("client[%d] closed connection\n", sockfd);
                }else if(nByte < 0){
                    // 连接异常
                    perror("epoll_ctl");
                    ret = epoll_ctl(epfd, EPOLL_CTL_DEL, sockfd, NULL);
                    if(-1 == ret){
                        perror("epoll_ctl");
                    }
                    close(sockfd);
                }
                // 正常的读取
                else{
                    for(j = 0; j < nByte; ++j){
                        buf[j] = toupper(buf[j]);
                    }
                    write(sockfd, buf, nByte);
                    write(STDOUT_FILENO, buf, nByte);
                }
            }
        }
    }
    close(listenfd);
    close(connfd);
    return 0;
}