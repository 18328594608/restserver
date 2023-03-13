//
// Created by 郭启成 on 2023/3/13.
//

#ifndef RSETSERVER_TOOL_H
#define RSETSERVER_TOOL_H

#include <memory>
#include <iostream>
#include <string>
#include <cstdio>
#include <mutex>

template<typename ...Args>
std::string string_format(const std::string & format, Args ...args)
{
    size_t size = snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
    std::unique_ptr<char[]> buf(new char[size]);
    snprintf(buf.get(), size, format.c_str(), args ...);
    return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

#endif //RSETSERVER_TOOL_H
