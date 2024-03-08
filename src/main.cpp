#include <iostream>
#include <MqttConnection.h>
#include <cstdlib>
#include <thread>

constexpr std::string topic = "teste";
constexpr std::string message = "OK - 2";

/*
 *
 *     tlsc.key_path = "/home/luan/Documents/aws/v3/private.pem.key";
    tlsc.cert_path = "/home/luan/Documents/aws/v3/certificate.pem.crt";
    tlsc.ca_path = "/home/luan/Documents/aws/v3/root-ca.pem";
    auto mc = MqttConnection("awyqq01axmcj7-ats.iot.us-east-2.amazonaws.com", 8883, tlsc);
 *
 * */

int main() {

    TlsConfig tlsc;
    tlsc.key_path = std::getenv("MQTT_KEY_PATH");
    tlsc.cert_path = std::getenv("MQTT_CERT_PATH");
    tlsc.ca_path = std::getenv("MQTT_CA_PATH");

    const char* host = std::getenv("MQTT_HOST");
    const char* port = std::getenv("MQTT_PORT");

    {
        using namespace std;
        cout << "MQTT_KEY_PATH = " << tlsc.key_path << endl;
        cout << "MQTT_CERT_PATH = " << tlsc.cert_path << endl;
        cout << "MQTT_CA_PATH = " << tlsc.ca_path << endl;
        cout << "MQTT_HOST = " << host << endl;
        cout << "MQTT_PORT = " << port << endl;
    }

   auto mc = MqttConnection(host, std::stoi(port), tlsc);

    for(int i = 0; i < 5; i++) {
        std::cout << "Send message" << std::endl;
        mc.publish(const_cast<std::string &>(topic), const_cast<std::string &>(message));
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }


    return 0;
}
