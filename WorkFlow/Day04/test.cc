#include "wfrest/HttpServer.h"
using namespace wfrest;

int main( ) {
    HttpServer svr;

    // curl -v http://ip:port/hello
    svr.GET("/hello", [](const HttpReq *req, HttpResp *resp) {
        resp->String("world\n");
    });
    // curl -v http://ip:port/data
    svr.GET("/data", [](const HttpReq *req, HttpResp *resp) {
        std::string str = "Hello world";
        resp->String(std::move(str));
    });

    // curl -v http://ip:port/post -d 'post hello world'
    svr.POST("/post", [](const HttpReq *req, HttpResp *resp) {
        // reference, no copy here
        std::string &body = req->body( );
        fprintf(stderr, "post data : %s\n", body.c_str( ));
    });

    if (svr.start(8888) == 0) {
        getchar( );
        svr.stop( );
    } else {
        fprintf(stderr, "Cannot start server");
        exit(1);
    }
    return 0;
}