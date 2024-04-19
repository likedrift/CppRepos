#ifndef __WD_CloudiskServer_HPP__ 
#define __WD_CloudiskServer_HPP__ 

#include <workflow/WFFacilities.h>
#include <wfrest/HttpServer.h>
#include <string>

using std::string;

class CloudiskServer
{
public:
    CloudiskServer(int cnt) 
    : _waitGroup(cnt)
    {}

    ~CloudiskServer() {}

    void start(unsigned short port);

    void loadModules();

    // void httpServerCallback(const wfrest::HttpReq *req, wfrest::HttpResp * resp, const char * path);
    // void httpServerCallback(const wfrest::HttpReq *req, wfrest::HttpResp * resp, SeriesWork * series);
    
    static void mysqlCallbackForRegister(wfrest::HttpResp * resp, WFMySQLTask * mysqltask);
    
    static void mysqlCallbackForLogin(string & encodedPassword, string & username, string & salt, 
                string & mysqlurl, wfrest::HttpResp * resp, WFMySQLTask * mysqltask, SeriesWork *series);
    
    static void mysqlCallbackForInfo(string & username, wfrest::HttpResp * resp, WFMySQLTask * mysqltask);

    static void mysqslCallbackForQuery(wfrest::HttpResp * resp, WFMySQLTask * mysqltask);
    // void mysqlCallback(WFMySQLTask * mysqltask);

private:
    //模块化的思维方式写代码
    void loadStaticResourceModule();
    void loadUserRegisterModule();
    void loadUserLoginModule();
    void loadUserInfoModule();
    void loadFileQueryModule();
    void loadFileUploadModule();
    void loadFileDownloadModule();

private:
    WFFacilities::WaitGroup _waitGroup;
    wfrest::HttpServer _httpserver;
};

#endif

