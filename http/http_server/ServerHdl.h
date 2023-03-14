//
// Created by 郭启成 on 2023/3/14.
//

#ifndef RSETSERVER_SERVERHDL_H
#define RSETSERVER_SERVERHDL_H
#include "wfrest/HttpServer.h"

using namespace wfrest;
class ServerHdl {
    public:
    static void handle_cmd_http_request(const HttpReq *req, HttpResp *resp);
};


#endif //RSETSERVER_SERVERHDL_H
