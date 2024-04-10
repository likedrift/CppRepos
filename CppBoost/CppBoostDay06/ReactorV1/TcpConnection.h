#ifndef __TCPCONNECTION_H__
#define __TCPCONNECTION_H__


/*
    如果Acceptor类的对象调用了accept函数的时候，就表明三次握手已经建立成功
    就可以使用该类的对象进行数据的收发
    发送数据 send
    接收数据 receive
*/

#include "SocketIO.h"
#include "InetAddress.h"
#include "Socket.h"
#include <string>

using std::string;

class SocketIO;

class TcpConnection{
public:
    explicit TcpConnection(int fd);
    ~TcpConnection();
    void send(const string & msg);
    string receive();

    // 为了调试
    string toString();

private:
    InetAddress getLocalAddr();
    InetAddress getPeerAddr();

private:
    SocketIO _socketIO;

    // 为了调试
    Socket _sock;
    InetAddress _localAddr;
    InetAddress _peerAddr;
};

#endif