#pragma once
#include <string>

struct TlsConfig {
    const char* ca_path;
    const char* key_path;
    const char* cert_path;
};


class MqttConnection {

public:
    MqttConnection(const char* host, int port, TlsConfig& tlsConfig);
    void publish(std::string& topic, std::string& message);
    void dispatch() const noexcept;

    static std::string exec(const char *command);

private:
    std::string getCommonArgs();
    std::string host;
    int port;
    TlsConfig tlsConfig;


};



