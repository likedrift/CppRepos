#include <iostream>
#include <unistd.h>
#include "TcpConnection.h"
#include "Acceptor.h"

using std::cout;
using std::endl;

void test01(){
    Acceptor acceptor("127.0.0.1", 12345);
    acceptor.ready(); // ip端口重用、bind、listen集一体

    // 走到这里 三次握手连接已建立
    TcpConnection con(acceptor.accept());

    cout << con.toString() << "has connected" << endl;

    while(1){
        cout << ">>receive msg from client: " << con.receive() << endl;
        con.send("hello, server here!\n");
        sleep(1);
    }
}

int main(void){
    test01();
    return 0;
}