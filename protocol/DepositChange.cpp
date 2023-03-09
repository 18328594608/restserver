//
// Created by 郭启成 on 2023/2/28.
//

#include "DepositChange.h"
#include "Log.h"
#include "Config.h"

DepositChange::DepositChange()
{
    m_login = 0;
}

DepositChange::~DepositChange() {

}

bool DepositChange::handle(Json json_data) {
    if (!json_data.has("login") || !json_data.has("price") || !json_data.has("comment"))
    {
        LOG_WARN( "HistoryOrders ： The passed argument does not exist");
        return false;
    }
    LOG_INFO("DepositChange :Received arguments ：{}", json_data.dump().c_str());

    m_login = json_data["login"].get<int>();
    m_price = json_data["price"].get<signed int>();
    m_comment = json_data["comment"].get<std::string>();
    return true;
}

void DepositChange::proxy_http_callback(WFHttpTask *http_task) {
    BaseProtocol::proxy_http_callback(http_task);
}

void DepositChange::get_request_body(std::string &str_body) {
    Json  body;
    body["id"] = ConfigManager::getInstance().getRequesID();
    body["method"] = "balance.update";

    Json params;
    params.push_back(m_login);
    params.push_back(std::to_string(m_price));
    params.push_back(m_comment);
    body.push_back("params", params);
    str_body = body.dump();
    LOG_INFO("DepositChange::request_body : {}", body.dump().c_str());
}

Json DepositChange::deal(const void *body, size_t len) {
    Json json_body = Json::parse(static_cast<const char *>(body));
    LOG_INFO("DepositChange::deal response body : {} ", json_body.dump().c_str());

    Json json_result = json_body["result"];
    if (!json_result.is_null())
    {
        std::string status = json_result["status"].get<std::string>();
        Json rsp_data;
        if (status == "success")
        {
            rsp_data["login"] = m_login;
            rsp_data["order"] = 0;
            rsp_data["profit"] = m_price;
        }
        return rsp_data;
    } else
    {
        Json err_data;
        return err_data;
        //TODO
    }
}
