//
// Created by 郭启成 on 2023/2/27.
//

#ifndef RSETSERVER_BASEPROTOCOL_H
#define RSETSERVER_BASEPROTOCOL_H

#include <memory>
#include "wfrest/HttpServer.h"

using namespace wfrest;


class BaseProtocol {
public:
    BaseProtocol();
    virtual ~BaseProtocol();
    virtual bool handle(Json);

    //proxy 转发请求的回调处理函数
    virtual void proxy_http_callback(WFHttpTask *http_task);

    //获取向服务器发送请求的body数据
    virtual void get_request_body(std::string&){}

    //处理函数
    virtual Json deal(const void *body, size_t len){Json data ; return data;};
    virtual std::string  get_cmd(){ return  "";};

private:
    void to_do(const void *body, size_t len, HttpResp *server_resp);

    //是否向客户端回包
    bool  m_send_to_client_;
};

typedef std::shared_ptr<BaseProtocol> BaseProtocolPtr;

#endif //RSETSERVER_BASEPROTOCOL_H
