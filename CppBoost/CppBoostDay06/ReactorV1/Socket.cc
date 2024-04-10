#include "Socket.h"

#include <sys/socket.h>
#include <stdio.h>
#include <unistd.h>
Socket::Socket(){
    _fd = socket(AF_INET, SOCK_STREAM, 0);
    printf("fd = %d\n",_fd);
    if(_fd == -1){
        perror("socket error");
        return;
    }
}

Socket::Socket(int fd)
:_fd(fd)
{ 

}

Socket::~Socket(){
    // 关闭文件描述符
    close(_fd);
}

int Socket::fd() const{
    return _fd;
}