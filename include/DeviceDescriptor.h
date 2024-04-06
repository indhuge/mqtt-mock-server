#include <MqttConnection.h>
#include <fstream>
#include <string>
#include <chrono>
#include <unordered_map>

struct ConnectionConfig {
    const char* host;
    const char* port;
};

class DeviceDescriptor {
public:
    DeviceDescriptor() = default;
    DeviceDescriptor(std::string deviceId, std::string topic, TlsConfig tlsConfig);
    static std::vector<DeviceDescriptor*> from(const char* filePath);
    static DeviceDescriptor* from(std::unordered_map<std::string, std::string> map);
    static std::vector<std::string> split(std::string, std::string delimiter);

private:
    std::string device_id;
    std::string topic;
    TlsConfig tlsConfig{};
    ConnectionConfig connectionConfig {};

};