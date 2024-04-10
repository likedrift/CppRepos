#include "Acceptor.h"
#include <iostream>

using std::cout;
using std::endl;

Acceptor::Acceptor(const string &ip, unsigned short port)
:_sock()
,_addr(ip, port)
{

}
Acceptor::~Acceptor(){

}
void Acceptor::ready(){
    setReuseAddr();
    setReusePort();
    bind();
    listen();
}

void Acceptor::setReuseAddr(){
    int opt = 1;
    int ret = setsockopt(_sock.fd(), SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if(ret == -1){
        perror("setsockopt");
        return;
    }
}
void Acceptor::setReusePort(){
    int opt = 1;
    int ret = setsockopt(_sock.fd(), SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));
    if(ret == -1){
        perror("setsockopt");
        return;
    }
}
void Acceptor::bind(){

    int ret = ::bind(_sock.fd(),(struct sockaddr *)(_addr.getInetAddressPtr()),sizeof(struct sockaddr));
    if(ret == -1){
        perror("bind");
        return;
    }
}
void Acceptor::listen(){

    // 开始监听客户端连接
    int ret = ::listen(_sock.fd(), 128);
    if(ret == -1){
        perror("listen");
        return;
    }
}
int Acceptor::accept(){
    // 后面两个参数为nullptr 表示不关心客户端的地址信息
    // 因此在连接建立后不会获取客户端的地址信息
    cout << _sock.fd() << endl;
    int connfd = ::accept(_sock.fd(), nullptr, nullptr);
    if(connfd == -1){
        perror("accept");
        return -1;
    }
    // 返回已建立连接的文件描述符
    cout << connfd << endl;
    return connfd;
}

int Acceptor::fd() const{
    return _sock.fd();
}

