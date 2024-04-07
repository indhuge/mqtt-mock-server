#include <iostream>
#include <MqttConnection.h>
#include <cstdlib>
#include <thread>
#include <sstream>
#include <random>
#include <nlohmann/json.hpp>
#include <DeviceDescriptor.h>
#include <MetricGenerator.h>
#include "Device.h"
#include <ThreadController.h>

int temperature = 25;
double pressure = 2.338;
int rpm = 600;

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_int_distribution dist(-30, 30);
std::uniform_real_distribution<double> d_pressure(-10, 10);
std::uniform_int_distribution d_rpm(-50, 50);


int _main(int args_c, const char** args) {

    const bool isLocal = std::strcmp(args[1], "local") == 0;
    std::cout << "Using mode: " << (isLocal ? "Local" : "AWS")  << std::endl;

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
    if(!isLocal)
    {
        tlsc.key_path = std::getenv("MQTT_KEY_PATH");
        tlsc.cert_path = std::getenv("MQTT_CERT_PATH");
        tlsc.ca_path = std::getenv("MQTT_CA_PATH");
    }

    const char* host = isLocal ? "localhost" : std::getenv("MQTT_HOST");
    const char* port = isLocal ? "1883" : std::getenv("MQTT_PORT");

    std::string deviceId;
    std::string type;
    std::string topic;


    {
        using namespace std;
        if(!isLocal)
        {

        cout << "MQTT_KEY_PATH = " << tlsc.key_path << endl;
        cout << "MQTT_CERT_PATH = " << tlsc.cert_path << endl;
        cout << "MQTT_CA_PATH = " << tlsc.ca_path << endl;
        cout << "MQTT_HOST = " << host << endl;
        cout << "MQTT_PORT = " << port << endl;
        }

        cout << "Enter the deviceId:";
        cin >> deviceId;
        cout << "Enter the type:";
        cin >> type;
        cout << "Enter the topic: ";
        cin >> topic;
        if(topic == "_")
        {
            topic = "nest/test";
            cout << "Using: " + topic << endl;
        }
        
    }

   auto mc = MqttConnection(host, std::stoi(port), tlsc);

    while(true) {

        nlohmann::json j;
        j["temperature"] = temperature + dist(mt);
        j["pressure"] = pressure + d_pressure(mt);
        j["rpm"] = rpm + d_rpm(mt);
        j["type"] = type;
        j["device_id"] = deviceId;

        mc.publish(topic, to_string(j));
        std::cout << topic << " -> " << j << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    
    return 0;
}

int main() {
    std::vector<std::unique_ptr<DeviceDescriptor>> d = DeviceDescriptor::from("/home/luan/Documents/mqtt-mock-server/exemple.conf");

    auto pMg = std::make_shared<MetricGenerator>();
    std::cout << pMg->generatePressure() << std::endl;
    std::cout << pMg->generateRpm() << std::endl;
    std::cout << pMg->generateTemperature() << std::endl;

    ThreadDescriptor td = {};
    td.interval = std::chrono::seconds(2);
    std::vector<Device> devices;
    std::vector<ThreadController> tcs;

    for(auto& x : d) {
        devices.emplace_back(*x, pMg);
    }

    for(auto& x : devices) {
        tcs.emplace_back(std::make_unique<Device>(x), td);
    }

    for(auto& x : tcs) {
        x.start();
    }
    if(!tcs.empty())
        tcs[0].join();

    return 0;
}