#include "TcpConnection.h"
#include <iostream>
#include <string.h>
#include <sstream>
#include <sys/socket.h>
#include <stdio.h>
#define MAX_SIZE 65535

using std::cout;
using std::endl;
using std::ostringstream;

TcpConnection::TcpConnection(int fd)
:_socketIO(fd)
,_sock(fd)
,_localAddr(getLocalAddr())
,_peerAddr(getPeerAddr())
{

}

TcpConnection::~TcpConnection(){

}

void TcpConnection::send(const string &msg){
    // if(!msg.empty()){
        _socketIO.writen(msg.c_str(),msg.size());
    // }
}
string TcpConnection::receive(){
    char buf[MAX_SIZE];
    memset(buf, 0, sizeof(buf));
    _socketIO.readLine(buf,sizeof(buf));
    
    return string(buf);
}

string TcpConnection::toString(){
    ostringstream oss;
    oss << _localAddr.ip() << ":"
        << _localAddr.port() << "---->"
        << _peerAddr.ip() << ":"
        << _peerAddr.port();

    return oss.str();
}

InetAddress TcpConnection::getLocalAddr(){
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr);
    cout << "_sock.fd() = " << _sock.fd() << endl;
    int ret = getsockname(_sock.fd(),(struct sockaddr *)&addr, &len);
    if(ret == -1){
        perror("getsockname error");
    }
    return InetAddress(addr);
}

InetAddress TcpConnection::getPeerAddr(){
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr);
    cout << "_sock.fd() = " << _sock.fd() << endl;
    int ret = getpeername(_sock.fd(),(struct sockaddr *)&addr, &len);
    if(ret == -1){
        perror("getpeername error");
    }
    return InetAddress(addr);
}