#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define PORT 8888
#define BUFFER_SIZE 4096

int main(){
    // 客户端的sockfd
    int client_fd;
    struct sockaddr_in server_addr;
    char buf[BUFFER_SIZE] = {0};
    int nByte; // 发送内容大小

    client_fd = socket(AF_INET,SOCK_STREAM,0);
    // sockfd创建失败
    if(client_fd == -1){
        perror("client socket error");
        exit(-1);
    }

    // 确保server_addr结构体的所有成员初始化为0，避免可能存在的垃圾数据导致的问题
    memset(&server_addr, 0, sizeof(server_addr));

    // 设置地址结构
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    // ipv4地址，INADDR_ANY表示愿意接收任何网络接口上的连接请求
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); 

    // 设置好sockaddr_in类型的各数据成员后，就可以进行connect了
    int ret = connect(client_fd,(struct sockaddr *)&server_addr,sizeof(server_addr));
    // connect如果链接建立成功，则返回0
    // 失败返回-1
    if(ret){
        perror("connect failed");
        exit(-1);
    }


    // 要执行的内容
    while(1){
        fgets(buf, sizeof(buf), stdin);
        write(client_fd, buf, strlen(buf));
        nByte = read(client_fd, buf , sizeof(buf));
        write(STDOUT_FILENO, buf , nByte);
    }

    close(client_fd);
    return 0;
} 