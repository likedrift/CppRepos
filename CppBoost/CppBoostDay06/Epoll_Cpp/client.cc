// epoll IO多路复用的c++写法
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
 

 void test(){
    // 1. 创建客户端的sockfd
    int clientfd = ::socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == clientfd){
        perror("socket");
        exit(-1);
    }

    // 2. 设置要连接的服务端协议、ip、端口号
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(8888);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    socklen_t length = sizeof(serverAddr);

    // 3. connect()连接服务端
    if(::connect(clientfd, (struct sockaddr*)&serverAddr,length) < 0){
        perror("connect");
        exit(-1);
    }

    cout << "conn has connected!..." << endl;

    // 4. 执行数据交互
    while(1){
        string line;
        cout << ">> please input som message: ";
        getline(cin, line);

        send(clientfd, line.data(), line.size(), 0);
        char buf[128] = {0};
        recv(clientfd, buf, sizeof(buf), 0);
        cout << "recv message from server: " << buf << endl;

    }
    close(clientfd);

 }

 int main(int argc, char **argv){
    test();
    return 0;
 }