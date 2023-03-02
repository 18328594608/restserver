//
// Created by 郭启成 on 2023/2/25.
//

#include "Server.h"
#include "../../protocol/ProtocolHdl.h"
#include "Log.h"

int Server::start() {
    HttpServer svr;
    svr.POST("/https", [](const HttpReq *req, HttpResp *resp)
    {
        auto str_body = req->body();
        //Json data = Json::parse(body);

        /*Json dat;
        dat["id"] = 1;
        dat["method"] = "balance.query";
        Json value;
       // value.push_back("balance", 1);
        //value.push_back("balance", 2);
        value.push_back( dat);
        //value.push_back(dat);
        resp->append_output_body(static_cast<const void *>(str_body.c_str()), str_body.size());*/

        Json value = R"("result": {"balance": "1932.94","equity": "1932.94","margin": "0","margin_free": "1932.94"})";
        resp->Json(value);
    });

    svr.POST("/", ProtocolHdl::handle_cmd_http_request);

    if (svr.start(8888) == 0)
    {
        LOG_INFO("Server Start Success port = 8888");
        getchar();
        svr.stop();
    } else
    {
        LOG_INFO( "Cannot start server");
        exit(1);
    }
    return 0;
}