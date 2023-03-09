//
// Created by 郭启成 on 2023/3/8.
//

#ifndef RSETSERVER_CONFIG_H
#define RSETSERVER_CONFIG_H

#include <iostream>
#include <fstream>
#include <json.hpp>

using json = nlohmann::json;

class ConfigManager {
public:
    static ConfigManager& getInstance() {
        static ConfigManager instance;
        return instance;
    }

    void readConfigFile(const std::string& filePath) {
        std::ifstream configFile(filePath);
        if (!configFile.is_open()) {
            throw std::runtime_error("Failed to open configuration file!");
        }

        try {
            json configData;
            configFile >> configData;

            network_io = configData["network_io"];
            log_level = configData["log_level"];
            id = configData["id"];
        }
        catch (const std::exception& e) {
            throw std::runtime_error("Failed to parse configuration file: " + std::string(e.what()));
        }
    }

    const std::string& getNewworkIo() const {
        return network_io;
    }

    int getRequesID() const {
        return id;
    }

    std::string getLogLevel() const {
        return log_level;
    }

private:
    ConfigManager() {}


    std::string network_io;
    int id;
    std::string log_level;
};



#endif //RSETSERVER_CONFIG_H
