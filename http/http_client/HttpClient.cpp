//
// Created by 郭启成 on 2023/2/26.
//

#include "HttpClient.h"
#include "workflow/HttpMessage.h"
#include "../../protocol/BaseProtocol.h"

void HttpClient::Http(std::string url, std::shared_ptr<BaseProtocol> protocol) {
    using namespace protocol;

    HttpServerTask *server_task = task_of(this);
    HttpReq *server_req = server_task->get_req();

    std::string http_url = url;
    if (strncasecmp(url.c_str(), "http://", 7) != 0 &&
        strncasecmp(url.c_str(), "https://", 8) != 0)
    {
        http_url = "http://" + http_url;
    }

    WFHttpTask *http_task = WFTaskFactory::create_http_task(http_url,
                                                            0,
                                                            0,
                                                            HttpClient::client_callback);

    auto *proxy_ctx = new ProxyCtx;
    proxy_ctx->url = http_url;
    proxy_ctx->server_task = server_task;
    proxy_ctx->is_keep_alive = server_req->is_keep_alive();
    proxy_ctx->protocol_ = protocol;
    http_task->user_data = proxy_ctx;

    ParsedURI uri;
    if (URIParser::parse(http_url, uri) < 0)
    {

        server_task->get_resp()->set_status(HttpStatusBadRequest);
        return;
    }

    std::string route;
    if (uri.path && uri.path[0])
    {
        route.append(uri.path);
    } else
    {
        route.append("/");
    }

    if(uri.query && uri.query[0])
    {
        route.append("?");
        route.append(uri.query);
    }

    HttpRequest *req = http_task->get_req();
    req->add_header_pair("Content-Type", "application/json");
    req->set_method("POST");
    req->set_request_uri(route);

    std::string request_body ;
    protocol->get_request_body(request_body);
    req->append_output_body(static_cast<const void *>(request_body.c_str()), request_body.size());

    http_task->get_resp()->set_size_limit(size_limit);
    **server_task << http_task;
}

void HttpClient::client_callback(WFHttpTask *http_task) {

    auto *proxy_ctx = static_cast<ProxyCtx *>(http_task->user_data);
    if (proxy_ctx != nullptr)
        proxy_ctx->protocol_->proxy_http_callback(http_task);
}



