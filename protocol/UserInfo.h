//
// Created by 郭启成 on 2023/2/27.
//
#include <ostream>
#include "BaseProtocol.h"
#include <vector>
#include "wfrest/HttpServer.h"
#include "wfrest/Json.h"
#include "workflow/WFFacilities.h"

#ifndef RSETSERVER_USERINFO_H
#define RSETSERVER_USERINFO_H


class UserInfo :public BaseProtocol {
public:
    UserInfo();
    virtual ~UserInfo();
    virtual bool handle(Json);

    virtual void proxy_http_callback(WFHttpTask *http_task);
    virtual void get_request_body(std::string&);

    virtual Json deal(const void *body, size_t len);
    virtual std::string  get_cmd(){ return  "userInfo";};
private:
    std::string m_token;
    std::vector<int> m_logins;
};


#endif //RSETSERVER_USERINFO_H
