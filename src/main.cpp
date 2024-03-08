#include <iostream>
#include <MqttConnection.h>
#include <cstdlib>
#include <thread>
#include <sstream>
#include <random>

std::string topic = "test/temperature";
int temperature = 25;

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_int_distribution dist(-3, 3);

/*
 *
 *     tlsc.key_path = "/home/luan/Documents/aws/v3/private.pem.key";
    tlsc.cert_path = "/home/luan/Documents/aws/v3/certificate.pem.crt";
    tlsc.ca_path = "/home/luan/Documents/aws/v3/root-ca.pem";
    auto mc = MqttConnection("awyqq01axmcj7-ats.iot.us-east-2.amazonaws.com", 8883, tlsc);
 *
 * */

int main() {

    std::stringstream ss;

   ss << " _____               _   ___   _                              ___\n";
   ss << "|_   _|             | | |  _| | |                            |_  |\n";
   ss << "  | |    _ __     __| | | |   | |__    _   _    __ _    ___    | |\n";
   ss << "  | |   | '_ \\   / _` | | |   | '_ \\  | | | |  / _` |  / _ \\   | |\n";
   ss << " _| |_  | | | | | (_| | | |   | | | | | |_| | | (_| | |  __/   | |\n";
   ss << "|_____| |_| |_|  \\__,_| | |_  |_| |_|  \\__,_|  \\__, |  \\___|  _| |\n";
   ss << "                        |___|                   __/ |        |___|\n";
   ss << "                                               |___/";


    std::cout << ss.str() << std::endl;

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

    while(true) {
        std::stringstream ms;
        ms << temperature + dist(mt);
        mc.publish(topic, (std::string &) std::move(ms.str()));
        std::cout << topic<< " " << ms.str() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }


    return 0;
}
