//
// Created by 郭启成 on 2023/2/26.
//
#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <workflow/WFTaskFactory.h>
#include "workflow/WFFacilities.h"

#include "wfrest/HttpServerTask.h"
#include "wfrest/HttpServer.h"

using namespace wfrest;
class HttpClient;
class BaseProtocol;
struct ProxyCtx
{
    std::string url;
    HttpServerTask *server_task;
    bool is_keep_alive;
    std::shared_ptr<BaseProtocol> protocol_;
};

class HttpClient :public HttpResp
{
public:
    HttpClient(const std::string& host, int port);

    HttpClient(const std::string &host);

    ~HttpClient();

    bool Connect();
    void Disconnect();
    bool IsConnected();

    bool Get(const std::string& path, std::string& response);
    bool Post(const std::string& path, const std::string& body, std::string& response);

    void Http(std::string url, std::shared_ptr<BaseProtocol> protocol);
    static void client_callback(WFHttpTask *task);

private:
    std::string url_;
    int port_;

    bool connected_;
    //std::shared_ptr<BaseProtocol> pro_;

    WFConnection* conn_;
    WFFacilities::WaitGroup wait_group_;

    std::string request_;
    std::string headers_;
    std::string body_;
    std::string response_;

    bool ConnectImpl();
    bool SendRequest(WFHttpTask* task, std::string& response);
};



#endif //RSETSERVER_HTTPCLIENT_H
