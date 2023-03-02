//
// Created by 郭启成 on 2023/2/28.
//

#include "HttpErrMsg.h"
#include "wfrest/Json.h"
#include "Log.h"

void HttpErrMsg::SendErrMsg(msg_errcode code, std::string msg, std::string cmd) {
    class::Json rsp_value;
    rsp_value["code"] = (int)code;
    rsp_value["message"] = msg;
    rsp_value["cmd"] = cmd;
    rsp_value["comment"] = "";

    LOG_ERROR("err : {},  cmd = {}",msg, cmd);
    Json(rsp_value);
}
