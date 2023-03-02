//
// Created by 郭启成 on 2023/2/28.
//

#include "HistoryOrders.h"
#include "Log.h"

HistoryOrders::HistoryOrders() {
     m_offset = 0;
     m_limit = 100;
}

HistoryOrders::~HistoryOrders() {

}

void HistoryOrders::proxy_http_callback(WFHttpTask *http_task) {
    BaseProtocol::proxy_http_callback(http_task);
}

bool HistoryOrders::handle(Json json_data) {
    if (!json_data.has("login") || !json_data.has("from") || !json_data.has("to"))
    {
        LOG_WARN( "HistoryOrders ： The passed argument does not exist");
        return false;
    }
    m_login = json_data["login"].get<int>();
    m_from = json_data["from"];
    m_to = json_data["to"];
    if(m_from > m_to)
    {
        return false;
    }
    return true;
}

void HistoryOrders::get_request_body(std::string &str_body) {
    Json  body;
    body["id"] = 1;
    body["method"] = "order.history";

    Json params;
    params.push_back(m_login);
    params.push_back("");       //symbol 品种，传""查询所有
    params.push_back(m_from);
    params.push_back(m_to);
    params.push_back(0);
    params.push_back(m_limit);  //单次查询数据量，上限100条

    body.push_back("params", params);
    str_body = body.dump();
    LOG_DEBUG( "HistoryOrders::get_request_body : request_body : {}", body.dump().c_str());
}

Json HistoryOrders::deal(const void *body, size_t len) {
    Json json_body = Json::parse(static_cast<const char *>(body));
    LOG_DEBUG( "HistoryOrders::deal response body : {}", json_body.dump().c_str());

    Json json_result = json_body["result"];
    if (!json_result.is_null())
    {
       // m_offset = json_result["offset"];
        //m_limit = json_result["limit"];
        Json::Array json_records = json_result["records"];
        Json rsp_data;
        for (int i = 0; i < json_records.size(); ++i) {
            Json jsonRecord;
            Json json_record =  json_records[i];

            std::string str_lot = json_record["lot"].get<std::string>();
            double d_lot = atof(str_lot.c_str()) * 100;
            double close_time = json_record["finish_time"].get<double>();

            jsonRecord["order"] = json_record["id"].get<int>();
            jsonRecord["symbol"] = json_record["symbol"].get<std::string>();
            jsonRecord["type"] = json_record["side"].get<int>();
            jsonRecord["volume"] = d_lot;
            jsonRecord["open_time"] = json_record["create_time"].get<double>();
            jsonRecord["open_price"] = json_record["price"].get<std::string>();
            jsonRecord["sl"] = json_record["sl"].get<std::string>();
            jsonRecord["tp"] = json_record["tp"].get<std::string>();
            jsonRecord["close_price"] = json_record["close_price"].get<std::string>();
            jsonRecord["close_time"] = static_cast<double>(close_time);
            jsonRecord["commission"] = json_record["fee"].get<std::string>();
            jsonRecord["swap"] =  json_record["swaps"].get<std::string>();
            jsonRecord["profit"] = json_record["profit"].get<std::string>();
            jsonRecord["comment"] = json_record["comment"].get<std::string>();
            rsp_data.push_back(jsonRecord);
        }
        return rsp_data;
    } else
    {
        //TODO
        Json err_data;
        return err_data;
    }

}
