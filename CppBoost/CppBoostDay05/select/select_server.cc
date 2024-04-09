#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>

#define SERV_PORT 8888

int main()
{
    int listenfd, connfd, sockfd;
    struct sockaddr_in serv_addr, clie_addr;
    socklen_t clie_addr_len;
    int ret, maxfd, maxi, i, j, nready, nByte;
    fd_set rset, allset;

    int client[FD_SETSIZE];        // FD_SIZE == 1024
    char buf[BUFSIZ], str[BUFSIZ]; // BUFSIZ == 8192

    // 1.创建套接字
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1)
    {
        perror("socket error");
        exit(-1);
    }

    // 2.地址复用
    int opt = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // 3.端口复用
    int opt2 = 1;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEPORT, &opt2, sizeof(opt2));

    // 4.绑定ip和端口号
    memset(&serv_addr, 0, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(SERV_PORT);
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    ret = bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    if (ret == -1)
    {
        perror("bind error");
        close(listenfd);
        exit(-1);
    }

    // 5.服务器监听
    ret = listen(listenfd, 128);
    if (ret == -1)
    {
        perror("listren error");
        close(listenfd);
        exit(-1);
    }

    printf("server is listening...\n");

    // 6.select类型IO多路复用
    maxfd = listenfd; // select第一个参数设置为listenfd
    maxi = -1;

    // 待监听的存放文件描述符数组的初始化
    for (i = 0; i < FD_SETSIZE; ++i)
    {
        client[i] = -1;
    }

    FD_ZERO(&allset); // 清空allset
    FD_SET(listenfd, &allset); // 将listenfd放在allset中进行监听

    while(1){
        rset = allset; // allset拷贝给rset
        // 6.1使用select负责监听，如果返回值大于0
        // 表明有满足条件的连接被监听到
        nready = select(maxfd + 1, &rset, NULL, NULL, NULL);
        if(nready < 0){
            perror("select error");
            close(listenfd);
            exit(-1);
        }


        // 如果监听到的是listenfd，表示有新的请求进来
        if(FD_ISSET(listenfd, &rset)){
            clie_addr_len = sizeof(clie_addr);
            // 7.有新的连接，accept肯定会有返回值
            connfd = accept(listenfd, (struct sockaddr *)&clie_addr, &clie_addr_len);
            if(connfd == -1){
                perror("accept error");
                exit(-1);
            }

            // 涉及网络字节序向本机字节序的转换
            printf("receive from %s from port %d\n",
                inet_ntop(AF_INET, &clie_addr.sin_addr, str, sizeof(str)),
                ntohs(clie_addr.sin_port));

            // 将新的连接加到数组client中，该数组就是为了存储
            // 建立连接的文件描述符，表明三次握手建立成功的连接的
            // 文件描述符
            for(i = 0; i < FD_SETSIZE; ++i){
                if(client[i] < 0){
                    client[i] = connfd;
                    break;
                }
            }

            // i超过了上限，即超过了能监听的最大文件描述符数量
            if(i == FD_SETSIZE){
                fputs("too many clients\n",stderr);
                exit(1);
            }

            // 将建立三次握手的文件描述符放在allset集合中进行
            // 继续监听，如果该文件描述符后续继续可读，表明
            // 有数据需要进行读写
            FD_SET(connfd, &allset);

            // 更新maxfd
            if(connfd > maxfd){
                maxfd = connfd;
            }

            // 更新maxi
            if(i > maxi){
                maxi = i;
            }

            // 如果nready为1，那就继续进行while循环
            // 而不用走6.3处的for循环，提升效率
            if(--nready == 0){
                continue;
            }
        }

        // 目的是为了遍历client数组，里面的元素如果为正
        // 就表明该文件描述符被监听到，就是老的连接
        // 就可以进行数据的发送与接收
        for(i = 0; i <= maxi; ++i){
            if((sockfd = client[i]) < 0){
                continue;
            }

            // 如果老的连接上数据，表明可以进行数据的传输
            // 可以进行read/write操作
            if(FD_ISSET(sockfd, &rset)){
                if((nByte = read(sockfd, buf, sizeof(buf))) == 0){
                    // 表明数据读完了（对应的缓冲区没有数据了）
                    // 也就是表明连接马上要断开了
                    close(sockfd);
                    printf("client[%d] closed connection\n", sockfd);
                    FD_CLR(sockfd, &allset);
                    client[i] = -1;
                }else if(nByte > 0){
                    for(j = 0; j < nByte; ++j){
                        buf[j] = toupper(buf[j]);
                    }
                    write(sockfd, buf, nByte);
                    write(STDOUT_FILENO, buf, nByte);
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