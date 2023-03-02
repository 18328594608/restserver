//
// Created by 郭启成 on 2023/2/27.
//

#include "UserInfo.h"
#include "../http/http_client/HttpClient.h"
#include "workflow/HttpMessage.h"
#include "Log.h"

UserInfo::UserInfo() {

}

UserInfo::~UserInfo() {
    m_token.clear();
    m_logins.clear();
}

bool UserInfo::handle(Json json_data) {
    if (!json_data.has("logins"))
    {
        LOG_WARN( "HistoryOrders ： The passed argument does not exist");
        return false;
    }
    auto res = json_data["logins"].get<Json::Array>();
    for (unsigned i = 0; i < res.size(); i++)
    {
        m_logins.push_back(res[i]);
    }

    if (m_logins.size() <= 0)
    {
        return false;
    }
    return true;
}

void UserInfo::proxy_http_callback(WFHttpTask *http_task) {

    BaseProtocol::proxy_http_callback(http_task);
}

void UserInfo::get_request_body(std::string& str_body){
    Json  body;
    body["id"] = 1;
    body["method"] = "balance.query";
    Json::Array json_array;
    for (unsigned i = 0; i < m_logins.size(); i++)
    {
        json_array.push_back(m_logins[i]);
    }
    body["params"] = json_array;
    str_body = body.dump();
    LOG_DEBUG("UserInfo::deal :request_body : {}", str_body.c_str());
}

Json UserInfo::deal(const void *body, size_t len) {
    Json json_body = Json::parse(static_cast<const char *>(body));
    Json json_result = json_body["result"];

    LOG_DEBUG("UserInfo::deal :result body : {}", json_result.dump().c_str());
    Json::Object userInfo;
    Json::Object marginInfo;
    std::string balance = json_result["balance"];
    std::string equity = json_result["equity"];
    std::string margin = json_result["margin"];
    std::string margin_free = json_result["margin_free"];

    userInfo["group"] = "";
    userInfo["enable"] = 0;
    userInfo["enable_change_password"] = 0;
    userInfo["enable_read_only"] = 0;
    userInfo["password_phone"] = "";
    userInfo["name"] = "";
    userInfo["address"] = "";
    userInfo["phone"] = "";
    userInfo["email"] = "";
    userInfo["agent_account"] = 0;
    userInfo["credit"] = 0.00;

    marginInfo["balance"] = std::stod(balance);
    marginInfo["leverage"] = 0;
    marginInfo["updated"] = 0;
    marginInfo["equity"] = std::stod(equity);
    marginInfo["volume"] = 0;
    marginInfo["margin"] = std::stod(margin);
    marginInfo["margin_free"] = std::stod(margin_free);
    marginInfo["margin_level"] = 0.00;
    marginInfo["margin_type"] = 0;
    marginInfo["level_type"] = 0;

    Json::Object  one_user;
    one_user["login"] = m_logins[0];
    one_user["userInfo"] = userInfo;
    one_user["marginInfo"] = marginInfo;

    std::string data = one_user.dump();

    Json  user;
    user.push_back(one_user);

    std::string data_user = user.dump();

    Json json_user;
    json_user.push_back("users", user);

    return json_user;
}
