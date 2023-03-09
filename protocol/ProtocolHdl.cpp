//
// Created by 郭启成 on 2023/2/27.
//

#include "ProtocolHdl.h"
#include "../http/http_client/HttpClient.h"
#include "BaseProtocol.h"
#include "UserInfo.h"
#include "DepositChange.h"
#include "HistoryOrders.h"
#include "HttpErrMsg.h"
#include "Log.h"
#include "Config.h"

std::shared_ptr<BaseProtocol> ProtocolFactory::create(const std::string &type) {
    {
        if (type == "userInfo") {
            return std::make_shared<UserInfo>();
        } else if (type == "depositChange") {
            return std::make_shared<DepositChange>();
        } else if (type == "historyOrders") {
            return std::make_shared<HistoryOrders>();
        } else {
            LOG_ERROR("Invalid operation type: {}" , type);
            return nullptr;
           // throw std::invalid_argument("Invalid operation type: " + type);
        }
    }
}

void ProtocolHdl::handle_cmd_http_request(const HttpReq *req, HttpResp *resp) {
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



