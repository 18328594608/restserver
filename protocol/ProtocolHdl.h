//
// Created by 郭启成 on 2023/2/27.
//

#ifndef RSETSERVER_PROTOCOLHDL_H
#define RSETSERVER_PROTOCOLHDL_H
#include <iostream>
#include <string>
#include <memory>
#include "wfrest/HttpServer.h"

using namespace wfrest;
class BaseProtocol;

class ProtocolFactory {
public:
    static std::shared_ptr<BaseProtocol> create(const std::string& type);
};

class ProtocolHdl{
public:
    static void handle_cmd_http_request(const HttpReq *req, HttpResp *resp);

};

#endif //RSETSERVER_PROTOCOLHDL_H
