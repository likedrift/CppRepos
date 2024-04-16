#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fstream>

using std::cout;
using std::endl;
using std::string;
using std::cerr;
using std::ifstream;

class HttpServer{
public:
    HttpServer(const string &ip, unsigned short port)
    :_ip(ip)
    ,_port(port)
    ,_sockfd(-1)
    {}

    ~HttpServer(){
        close(_sockfd);
    }

    void start();
    void recvAndShow();
    void respPic(int fd);

private:
    string _ip;
    unsigned short _port;
    int _sockfd;
};

void HttpServer::start(){
    _sockfd = ::socket(AF_INET, SOCK_STREAM, 0);
    if(-1 == _sockfd){
        perror("socket");
        exit(-1);
    }

    struct sockaddr_in serverAddr; // <netinet/in.h>
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(_port);
    serverAddr.sin_addr.s_addr = inet_addr(_ip.c_str());

    int ret = ::bind(_sockfd,(struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if(-1 == ret){
        perror("bind");
        exit(-1);
    }

    ret = ::listen(_sockfd, 128);
    if(-1 == ret){
        perror("listen");
        exit(-1);
    }
}

void HttpServer::recvAndShow(){
    while(true){
        int netfd = accept(_sockfd, nullptr, nullptr);
        if (-1 == netfd){
            perror("accept");
            exit(-1);
        }
        // 创建一个接收缓冲区
        char buf[4096] = {0};

        ssize_t sret = recv(netfd, buf, sizeof(buf), 0);
        cout << "sret = " << sret << ", buf = " << buf << endl;
        respPic(netfd);
        close(netfd);
    }
}

void HttpServer::respPic(int fd){
    string startLine = "HTTP/1.1 200 OK\r\n";
    string headers = "Server: MyHttpServer\r\n";
    headers += "Content-Type: image/jpeg\r\n";
    string emptyLine = "\r\n";
    string response = startLine + headers + emptyLine;
    send(fd, response.c_str(), response.size(), 0);
    
    char buf[4096] = {0};
    ifstream ifs("1.jpg", std::ios::binary);
    if(!ifs){
        cerr << "Failed to open file" << endl;
        exit(-1);
    }

    while(!ifs.eof()){
        ifs.read(buf, sizeof(buf));
        int ret = send(fd, buf, ifs.gcount(), 0);
        if(-1 == ret){
            perror("send");
            exit(-1);
        }
    }
    ifs.close();
}

void test01(){
    HttpServer server("192.168.174.128",1234);
    server.start();
    server.recvAndShow();

}

int main(void){
    test01();
    return 0;
}