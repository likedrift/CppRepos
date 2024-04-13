#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <poll.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define SERV_PORT 8888
#define OPEN_MAX 1024

int main(){
    int i, j, n, maxi;
    int nready, ret;
    int listenfd, connfd, sockfd;
    // BUFSIZ--8192 INET_ADDRSTRLEN--16
    char buf[BUFSIZ], str[INET_ADDRSTRLEN];
    struct sockaddr_in serv_addr, clie_addr;
    socklen_t clie_addr_len;
    struct pollfd client[OPEN_MAX];

    // 1. 创建套接字
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

    // 4. 绑定ip与端口号
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.2");

    ret = bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));
    if(-1 == ret){
        perror("bind");
        close(listenfd);
        exit(-1);
    }

    // 5.服务端监听
    ret = listen(listenfd, 128);
    if(-1 == ret){
        perror("listen");
        close(listenfd);
        exit(-1);
    }

    printf("server is listening...\n");

    /*
        struct pollfd{
            int fd; // 文件描述符
            short events; // 监听的事件掩码
            short revents; // 实际发生的事件掩码
        }
    */

    // 6. poll的IO多路复用
    client[0].fd = listenfd;
    client[0].events = POLLIN;

    // 对待监听的存放文件描述符数组进行初始化，从1开始，0已经存放listenfd
    for(i = 1; i < OPEN_MAX; ++i){
        client[i].fd = -1; // 数组内容初始化为-1
    }

    // 一开始只有一个listenfd在数组里，poll的第二个参数是指
    // 结构体数组中pfd结构体的个数，即需要监控的文件描述符总数
    // 第一次进while循环，自然只有1个listenfd文件描述符
    maxi = 0;

    while(1){
        // 6.1 使用poll负责监听，如果返回值大于0
        // 表示有满足条件的连接被监听到
        nready = poll(client, maxi + 1, -1);
        if(nready < 0){
            perror("poll");
            close(listenfd);
            exit(-1);
        }

        // 6.2 如果监听到的是listenfd，表示有新的客户端连接请求
        if(client[0].revents & POLLIN){
            clie_addr_len = sizeof(clie_addr);

            // 7. accept用于接受一个新的客户端请求
            // 服务端调用accept函数时，会阻塞等待
            // 返回新链接的套接字描述符
            // 因为已经监听到就绪，所以不会阻塞等待，而是立即连接
            connfd = accept(listenfd, (struct sockaddr *)&clie_addr, &clie_addr_len);
            if(-1 == connfd){
                perror("accept");
                exit(-1);
            }

            // 打印到屏幕
            printf("received from %s at port %d\n",
                   inet_ntop(AF_INET, &clie_addr.sin_addr.s_addr, str, sizeof(str)),
                   ntohs(clie_addr.sin_port));
            
            // 将新的连接加到pollfd结构体数组的client中
            // 存储的fd即三次握手后建立成功连接的文件描述符
            for(i = 1; i < OPEN_MAX; ++i){
                if(client[i].fd < 0){ // 初始化的时候全部置成-1了
                    client[i].fd = connfd; // 放到最小可用位置
                    break;
                }
            }
            

            // i超过最大能见听得文件描述符个数
            if(i == OPEN_MAX){
                fputs("clients limits overtaked\n", stderr);
                exit(1);
            }

            client[i].events = POLLIN;
        
            if(i > maxi){
                maxi = i; // 如果新增的文件描述符位置是之前最大的后面，那就要把i给max
            }

            // nready为1，即只有一个listenfd就绪，那就继续进行while循环
            // 而不用继续往下走
            if(--nready == 0){
                continue;
            }
        }

        // 6.3 目的是为了遍历client数组，里面的元素如果为正，就
        // 表明该文件描述符被监听到，就是老的连接，就可以进行数据的发送和接收 
        // client[0].fd是listenfd，其他的都是connfd 
        for(i = 1; i <= maxi; ++i){
            if((sockfd = client[i].fd) < 0){
                continue;
            }

            // 老的连接上有数据传送到服务器
            // 如果老的连接上有数据，表明可以进行数据的传输
            // 可以进行read/write
            if(client[i].revents & POLLIN){
                if((n = read(sockfd, buf, sizeof(buf))) < 0){
                    if(errno == ECONNRESET){ // read遇到连接被重置的问题
                        printf("client[%d] abort connect\n", i);
                        close(sockfd);
                        client[i].fd = -1;
                    }else{
                        perror("read n = 0");
                    }
                }else if(n > 0){ // 读取到的字节数大于0
                    // 转成大写
                    for(j = 0; j < n; ++j){
                        buf[j] = toupper(buf[j]);
                    }
                    // 传回给客户端
                    write(sockfd, buf, n);
                    write(STDOUT_FILENO, buf, n);
                }else{ // 读取到的字节数为0
                    close(sockfd);
                    printf("client[%d] closed connection\n", sockfd);
                    client[i].fd = -1;
                }

                if(--nready == 0){
                    break;
                }
            }
        }
    }
    close(listenfd);
    close(connfd);
    return 0;
}