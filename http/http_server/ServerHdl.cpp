//
// Created by 郭启成 on 2023/3/14.
//

#include "ServerHdl.h"
#include "../http/http_client/HttpClient.h"
#include "../protocol/BaseProtocol.h"
#include "../http/HttpErrMsg.h"
#include "protocolHdl/ProtocolHdl.h"
#include "Config.h"

void ServerHdl::handle_cmd_http_request(const HttpReq *req, HttpResp *resp) {
    //TODO ERR handle

    auto body = req->body();
    Json json = Json::parse(body);
    std::string cmd = json["cmd"];
    std::shared_ptr<BaseProtocol> factory = ProtocolFactory::create(cmd);
    if (factory == nullptr)
    {
        HttpErrMsg *err_cast = static_cast<HttpErrMsg *>(resp);
        err_cast->SendErrMsg(prase_err , "Param invalid" , cmd);
        return;
    }

    if (!json["data"].is_null())
    {
        if (factory->handle(json["data"]))
        {
            HttpClient *server_req_cast = static_cast<HttpClient *>(resp);

            const std::string url = ConfigManager::getInstance().getNewworkIo();
            //发送http请求
            server_req_cast->Http(url, factory);
        } else
        {
            HttpErrMsg *err_cast = static_cast<HttpErrMsg *>(resp);
            err_cast->SendErrMsg(prase_err , "Param handle erro" , cmd);
        }
    }
    else
    {
        HttpErrMsg *err_cast = static_cast<HttpErrMsg *>(resp);
        err_cast->SendErrMsg(prase_err , "Param is empty" , cmd);
    }
}
