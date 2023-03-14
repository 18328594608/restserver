//
// Created by 郭启成 on 2023/2/24.
//
#include "Config.h"
#include <iostream>
#include "http/http_server/Server.h"
#include "base/Log.h"
#include "base/server/Server.h"
#include "base/server/CoreServer.h"
#include "base/server/wsServer.h"
#include "base/server/PraseServer.h"
int main()
{
    try {
        ConfigManager::getInstance().readConfigFile("config.json");
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
    LogLevel level =  Logger::getInstance().stringLogLevel(ConfigManager::getInstance().getLogLevel());
    Logger::getInstance().setLevel(level);
    Instance(CPraseServer)->start(8);
    Instance(CCoreServer)->start(16);
    Instance(CWsServer)->start(8);
    return 0;
}

