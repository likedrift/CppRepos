#include "SocketIO.h"
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
SocketIO::SocketIO(int fd)
:_fd(fd)
{

}

SocketIO::~SocketIO(){
    close(_fd);
}

int SocketIO::readn(char *buf, int len){
    int left = len;
    // 初始化指针pstr指向用户提供的缓冲区起始位置
    // 后续用作当前读取位置
    char *pstr = buf; 
    int ret = 0;

    while(left > 0){
        ret = read(_fd, pstr, left);

        // EINTR:中断系统调用
        // 当一个正在执行的系统调用被信号中断时
        // 操作系统会返回EINTR错误代码
        // 以通知应用程序该系统调用被中断

        if(ret == -1 && errno == EINTR){
            continue;
        }else if(ret == -1){
            perror("read error -1");
            return -1;
        }else if(ret == 0){ // EOF
            break;
        }else{
            pstr += ret;
            left -= ret;
        }
    }
    return len - left;
}

int SocketIO::readLine(char *buf, int len){
    int left = len - 1; // -1是为了保留空间放置 \0 字符作为字符串结束标识
    char *pstr = buf;
    int ret = 0, total = 0;

    while(left > 0){
        // MSG_PEEK:将数据从缓冲区读出来，但是不会将数据从缓冲区中移除
        ret = recv(_fd, pstr, left, MSG_PEEK);
        if(ret == -1 && errno == EINTR){
            continue;
        }else if(ret == -1){
            perror("readLine error");
            return -1;
        }else if(ret == 0){
            break;
        }else{
            for(int idx = 0; idx < ret; ++idx){
                if(pstr[idx] == '\n'){
                    int sz = idx + 1;
                    readn(pstr, sz);
                    pstr += sz;
                    *pstr = '\0';

                    return total + sz;
                }
            }
            readn(pstr, ret);
            total += ret;
            pstr += ret;
            left -= ret;
        }
    }
    *pstr = '\0';

    return total - left;
}

int SocketIO::writen(const char *buf, int len){
    int left = len; // left是剩余待写入数据的长度
    // pstr指向 buf首元素位置
    // 用于跟踪当前待写入数据的起始位置
    const char *pstr = buf;
    int ret = 0; // 用于暂存每次调用write()系统调用的返回值

    while(left > 0){ // 还有数据可读 即 left > 0
        // write期望一次将pstr指向的、长度为left的字节序列写入_fd中
        // 写入_fd：将用户程序指定的一段数据发送到与特定文件描述符关联的IO通道中
        ret = write(_fd, pstr, left);
        if(ret == -1 && errno == EINTR){ // write中断，忽略此次错误，继续下一轮循环
            continue;
        }else if(ret == -1){ // 其他写入错误
            perror("writen error -1");
            return -1;
        }else if(ret == 0){ // 无更多数据需要写入或连接已关闭 跳出循环
            break;
        }else{
            pstr += ret;
            left -= ret;
        }
    }
    return len - left;
}