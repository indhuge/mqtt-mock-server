//
// Created by luan on 3/8/24.
//

#include <utility>
#include <array>
#include <memory>
#include <sstream>
#include <iostream>

#include "../include/MqttConnection.h"


MqttConnection::MqttConnection(const char* host, int port, TlsConfig& tlsConfig) :
host(host), port(port), tlsConfig(tlsConfig) {
}

void MqttConnection::dispatch() const noexcept {

}

void MqttConnection::publish(std::string topic, std::string message) {
    std::stringstream ss;
    ss << "mqtt pub " << getCommonArgs() ;
    ss << " -t " << topic << " -m '" << message << "'";
    std::cout << ss.str() << std::endl;
    exec(ss.str().c_str());
}

std::string MqttConnection::exec(const char *command) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command, "r"), pclose);
    if(!pipe) {
        throw std::runtime_error("popen() failed");
    }
    while(fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

std::string MqttConnection::getCommonArgs() {
    std::stringstream ss;
    ss << " -h " << host << " -p " << port;
    if(tlsConfig)
        ss << " -s --cafile " << tlsConfig.ca_path << " --cert " << tlsConfig.cert_path << " --key " << tlsConfig.key_path;
    ss << " -d";
    return ss.str();
}

