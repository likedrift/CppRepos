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
    // 1. 创建客户端socket
    int client_fd; 
    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == client_fd){
        perror("socket");
        exit(-1);
    }

    // 2. 设置要连接的服务端信息
    struct sockaddr_in server_addr;
    memset(&server_addr, 0, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERV_PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERV_IP);

    // 3. 准备完成后可以进行连接
    int ret = connect(client_fd,(struct sockaddr*)&server_addr,sizeof(server_addr));
    if(-1 == ret){
        perror("connect");
        exit(-1);
    }

    // 4. 走到这说明已经建立好连接
    // 客户端执行需要的行为
    char buf[BUFFER_SIZE] = {0};
    int nByte = 0;// read读取到的字节数
    while(1){
        fgets(buf, sizeof(buf), stdin);
        write(client_fd, buf, strlen(buf));
        nByte = read(client_fd, buf, sizeof(buf));
        write(STDOUT_FILENO, buf, nByte);
    }
    close(client_fd);
    return 0;
}