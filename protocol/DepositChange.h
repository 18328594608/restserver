//
// Created by 郭启成 on 2023/2/28.
//

#ifndef RSETSERVER_DEPOSITCHANGE_H
#define RSETSERVER_DEPOSITCHANGE_H

#include "BaseProtocol.h"
#include "wfrest/HttpServer.h"
#include "wfrest/Json.h"
#include "workflow/WFFacilities.h"

class DepositChange :public BaseProtocol{
public:
    DepositChange();
    virtual ~DepositChange();
    virtual bool handle(Json);

    virtual void proxy_http_callback(WFHttpTask *http_task);
    virtual void get_request_body(std::string&);

    virtual Json deal(const void *body, size_t len);
    virtual std::string  get_cmd(){ return  "depositChange";};
private:
    int m_login;
    signed int m_price;
    std::string m_comment;
};


#endif //RSETSERVER_DEPOSITCHANGE_H
