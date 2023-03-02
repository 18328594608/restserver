//
// Created by 郭启成 on 2023/2/28.
//

#ifndef RSETSERVER_HTTPMSG_H
#define RSETSERVER_HTTPMSG_H
#include "wfrest/HttpServer.h"
using namespace wfrest;

enum msg_errcode
{
    ok = 0,
    prase_err,
    protocol_err,
    login_err,
    open_err,
    queryOrder_err,
    chart_err,
    db_err,
    instrument_err,
    token_err,
    mt4_conn_err,
    deposit_err,
    forceClose_err,
    plan_err,
    delUser_err,
    batchClose_err,
    delOrder_err
};

class HttpErrMsg :public HttpResp{
public:
    void SendErrMsg(msg_errcode code, std::string msg, std::string cmd);
};


#endif //RSETSERVER_HTTPMSG_H
