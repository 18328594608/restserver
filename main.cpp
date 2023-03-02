//
// Created by 郭启成 on 2023/2/24.
//
#include <iostream>
#include "http/http_server/Server.h"
#include "base/Log.h"
int main()
{
    Server *server = new Server();
    Logger::getInstance().setLevel(TRACE);
    server->start();

    return 0;
}

