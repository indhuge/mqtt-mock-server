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
    friend class Device;
public:
    DeviceDescriptor() = default;
    DeviceDescriptor(std::string deviceId, std::string topic, TlsConfig tlsConfig);
    static std::vector<std::unique_ptr<DeviceDescriptor>> from(const char* filePath);
    static std::unique_ptr<DeviceDescriptor> from(std::unordered_map<std::string, std::string> map);
    static std::vector<std::string> split(std::string, std::string delimiter);

    std::string getDeviceId() const;


private:
    std::string device_id;
    std::string topic;
    TlsConfig tlsConfig{};
    ConnectionConfig connectionConfig {};

};