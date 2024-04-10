#ifndef __INETADDRESS_H__
#define __INETADDRESS_H__

#include "arpa/inet.h"
#include <string>

using std::string;

class InetAddress{

public:
    // 两种 使用ip和端口号初始化InetAddress的方式
    InetAddress(const string &ip, unsigned short port); // 基本用这个
    InetAddress(const struct sockaddr_in &addr); // getPeerAddr和getLocalAddr会用到
    ~InetAddress();
    string ip() const;
    unsigned short port() const;
    const struct sockaddr_in *getInetAddressPtr() const;

private:
    struct sockaddr_in _addr;
};

#endif