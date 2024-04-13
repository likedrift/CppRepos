#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#define SERV_IP "127.0.0.1"
#define SERV_PORT 8888
#define BUFFER_SIZE 4096


int main(){
    int client_fd;
    struct sockaddr_in server_addr;
    char buf[BUFFER_SIZE] = {0};
    int nByte;

    // 1. 创建socket
    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    // socket创建失败
    if(client_fd == -1){
        perror("socket");
        exit(-1);
    }

    memset(&server_addr, 0, sizeof(server_addr));
    // 2.设置连接的信息
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERV_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERV_IP);

    // 设置好要连接的服务端各数据成员后，就可以进行连接
    int ret = connect(client_fd,(sockaddr *)&server_addr,sizeof(server_addr));
    if(ret == -1){
        perror("connect");
        exit(-1);
    }

    // 连接成功
    while(1){
        fgets(buf, sizeof(buf), stdin);
        write(client_fd, buf, strlen(buf));
        nByte = read(client_fd, buf, sizeof(buf));
        write(STDOUT_FILENO, buf, nByte);
    }
    close(client_fd);
    return 0;

}