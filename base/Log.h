//
// Created by 郭启成 on 2023/2/28.
//

#ifndef RSETSERVER_LOG_H
#define RSETSERVER_LOG_H


#include <iostream>
#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/daily_file_sink.h>
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

// 定义日志级别
enum LogLevel {
    TRACE,
    DEBUG,
    INFO,
    WARN,
    ERROR,
    CRITICAL
};

// 日志类，使用单例模式
class Logger {
public:
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }

    // 设置日志级别
    void setLevel(LogLevel level) {
        switch (level) {
            case TRACE:
                logger_->set_level(spdlog::level::trace);
                logger_->flush_on(spdlog::level::trace);
                break;
            case DEBUG:
                logger_->set_level(spdlog::level::debug);
                break;
            case INFO:
                logger_->set_level(spdlog::level::info);
                break;
            case WARN:
                logger_->set_level(spdlog::level::warn);
                break;
            case ERROR:
                logger_->set_level(spdlog::level::err);
                break;
            case CRITICAL:
                logger_->set_level(spdlog::level::critical);
                break;
        }
    }

    // 获取日志对象
    std::shared_ptr<spdlog::logger> getLogger() {
        return logger_;
    }

    std::shared_ptr<spdlog::logger> getConsoleLogger() {
        return console_;
    }

private:
    Logger() {
        // 初始化日志对象
        std::string log_filename = "logs/" + getLogFilename();
        logger_ = spdlog::rotating_logger_mt("Logger", log_filename.c_str(), 1024 * 1024 * 20, 50);
        logger_->flush_on(spdlog::level::info);
        console_ = spdlog::stdout_color_mt("console");
    }

    // 获取日志文件名
    std::string getLogFilename() {
        std::time_t t = std::time(nullptr);
        std::tm tm = *std::localtime(&t);
        char buffer[64];
        std::strftime(buffer, sizeof(buffer), "%Y-%m-%d.log", &tm);
        return buffer;
    }

    std::shared_ptr<spdlog::logger> logger_;
    std::shared_ptr<spdlog::logger> console_;
};

// 定义日志访问宏函数
#define LOG_TRACE(...) SPDLOG_LOGGER_TRACE(Logger::getInstance().getLogger(), __VA_ARGS__);      SPDLOG_LOGGER_TRACE(Logger::getInstance().getConsoleLogger(), __VA_ARGS__)
#define LOG_DEBUG(...) SPDLOG_LOGGER_DEBUG(Logger::getInstance().getLogger(), __VA_ARGS__) ;     SPDLOG_LOGGER_DEBUG(Logger::getInstance().getConsoleLogger(), __VA_ARGS__)
#define LOG_INFO(...) SPDLOG_LOGGER_INFO(Logger::getInstance().getLogger(), __VA_ARGS__)  ;      SPDLOG_LOGGER_INFO(Logger::getInstance().getConsoleLogger(), __VA_ARGS__)
#define LOG_WARN(...) SPDLOG_LOGGER_WARN(Logger::getInstance().getLogger(), __VA_ARGS__)  ;      SPDLOG_LOGGER_WARN(Logger::getInstance().getConsoleLogger(), __VA_ARGS__)
#define LOG_ERROR(...) SPDLOG_LOGGER_ERROR(Logger::getInstance().getLogger(), __VA_ARGS__) ;     SPDLOG_LOGGER_ERROR(Logger::getInstance().getConsoleLogger(), __VA_ARGS__)
#define LOG_CRITICAL(...) SPDLOG_LOGGER_CRITICAL(Logger::getInstance().getLogger(), __VA_ARGS__);SPDLOG_LOGGER_CRITICAL(Logger::getInstance().getConsoleLogger(), __VA_ARGS__)



#endif //RSETSERVER_LOG_H
