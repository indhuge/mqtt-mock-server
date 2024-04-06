#include <DeviceDescriptor.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <unordered_map>

DeviceDescriptor::DeviceDescriptor(std::string deviceId, std::string topic, TlsConfig tlsConfig):
device_id(deviceId), topic(topic), tlsConfig(tlsConfig)
{}

std::unique_ptr<DeviceDescriptor> DeviceDescriptor::from(std::unordered_map<std::string, std::string> map) {
    auto pDD = new DeviceDescriptor();
    for(const auto& x : map){
        if(x.first == "device_id")
            pDD->device_id = x.second;
        else if(x.first == "topic")
            pDD->topic = x.second;
        else if(x.first == "mode") {
            if(x.second == "aws") {
                pDD->tlsConfig.key_path = std::getenv("MQTT_KEY_PATH");
                pDD->tlsConfig.cert_path = std::getenv("MQTT_CERT_PATH");
                pDD->tlsConfig.ca_path = std::getenv("MQTT_CA_PATH");

                pDD->connectionConfig.host = std::getenv("MQTT_HOST");
                pDD->connectionConfig.port = std::getenv("MQTT_PORT");
            }
            else {
                pDD->connectionConfig.host = "localhost";
                pDD->connectionConfig.port = "1883";
            }

        }
    }
    return std::make_unique(pDD);
}

std::vector<std::unique_ptr<DeviceDescriptor>> DeviceDescriptor::from(const char *filePath) {
    std::ifstream file(filePath);
    if(!file.is_open()) return {};
    std::vector<std::unordered_map<std::string, std::string>> dds_props;

    int i = -1;
    for(std::string a ; std::getline(file, a);) {
        if(a.empty()) continue;
        if(a == "[DEVICE]"){
            dds_props.emplace_back();
            i++;
            continue;
        }
        auto prop = split(a, "=");
        dds_props[i].insert(std::make_pair(prop[0], prop[1]));
    }

    std::vector<std::unique_ptr<DeviceDescriptor>> result;
    for (const auto& x : dds_props) {
        result.push_back(from(x));
    }

    return result;
}



std::vector<std::string> DeviceDescriptor::split(std::string s, std::string delimiter) {
    std::vector<std::string> result;
    std::string token;
    int pos = 0;
    pos = s.find(delimiter);
    while (pos != std::string::npos){
        token = s.substr(0, pos);
        result.push_back(token);
        s.erase(0, pos + delimiter.length());
        pos = s.find(delimiter);
    }
    result.push_back(s);
    return result;
}

std::string DeviceDescriptor::getDeviceId() const
{
    return device_id;
}

