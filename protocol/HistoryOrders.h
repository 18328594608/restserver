//
// Created by 郭启成 on 2023/2/28.
//

#ifndef RSETSERVER_HISTORYORDERS_H
#define RSETSERVER_HISTORYORDERS_H


#include "BaseProtocol.h"
#include "wfrest/HttpServer.h"
#include "wfrest/Json.h"

class HistoryOrders : public BaseProtocol {
public:
    HistoryOrders();
    virtual ~HistoryOrders();
    virtual bool handle(Json);

    virtual void proxy_http_callback(WFHttpTask *http_task);
    virtual void get_request_body(std::string&);

    virtual Json deal(const void *body, size_t len);
    virtual std::string  get_cmd(){ return  "historyOrders";};
private:
    std::string m_token;
    int m_login;
    int32_t m_from;
    int32_t m_to;
    int m_limit;
    int m_offset;
};


#endif //RSETSERVER_HISTORYORDERS_H
