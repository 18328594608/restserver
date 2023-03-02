//
// Created by 郭启成 on 2023/2/27.
//

#include "BaseProtocol.h"
#include "../http/http_client/HttpClient.h"
#include "workflow/HttpMessage.h"
#include "wfrest/ErrorCode.h"
#include "HttpErrMsg.h"

BaseProtocol::BaseProtocol() {

}

BaseProtocol::~BaseProtocol() {

}

bool BaseProtocol::handle(Json data) {
    return false;
}

void BaseProtocol::proxy_http_callback(WFHttpTask *http_task) {
    int state = http_task->get_state();
    int error = http_task->get_error();

    auto *proxy_ctx = static_cast<ProxyCtx *>(http_task->user_data);
    HttpServerTask *server_task = proxy_ctx->server_task;
    protocol::HttpResponse *http_resp = http_task->get_resp();
    HttpResp *server_resp = server_task->get_resp();

    if (state == WFT_STATE_SYS_ERROR && error == ECONNRESET)
        state = WFT_STATE_SUCCESS;

    if (state == WFT_STATE_SUCCESS)
    {
        const void *body;
        size_t len;
        if (http_resp->get_parsed_body(&body, &len))
        {
            to_do(body, len, server_resp);
        }
    } else
    {
        const char *err_string;
        int error = http_task->get_error();

        if (state == WFT_STATE_SYS_ERROR)
            err_string = strerror(error);
        else if (state == WFT_STATE_DNS_ERROR)
            err_string = gai_strerror(error);
        else if (state == WFT_STATE_SSL_ERROR)
            err_string = "SSL error";
        else /* if (state == WFT_STATE_TASK_ERROR) */
            err_string = "URL error (Cannot be a HTTPS proxy)";

        std::string errmsg;
        errmsg.reserve(64);
        errmsg.append(proxy_ctx->url);
        errmsg.append(" : Fetch failed. state = ");
        errmsg.append(std::to_string(state));
        errmsg.append(", error = ");
        errmsg.append(std::to_string(http_task->get_error()));
        errmsg.append(" ");
        errmsg.append(err_string);

        HttpErrMsg *err_cast = static_cast<HttpErrMsg *>(server_resp);
        err_cast->SendErrMsg(protocol_err, errmsg, get_cmd());
    }
}

void BaseProtocol::to_do(const void *body, size_t len, HttpResp *server_resp) {
    Json json_body = Json::parse(static_cast<const char *>(body));
    if (json_body["error"].is_null())
    {
        Json json_data = deal(body,len);
        Json rsp_value;
        rsp_value["code"] = 0;
        rsp_value["message"] = "";
        rsp_value["cmd"] = get_cmd();
        rsp_value["comment"] = "";
        rsp_value.push_back("data", json_data);
        server_resp->Json(rsp_value);
    } else
    {
        //TODO
        Json err_json = json_body["error"];
        std::string err_msg = err_json["message"];
        int code = err_json["code"];
        HttpErrMsg *err_cast = static_cast<HttpErrMsg *>(server_resp);

        err_cast->SendErrMsg(msg_errcode(code), err_msg, get_cmd());
    }

}
