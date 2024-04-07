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

int main(int argc, char** argv) {

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
    std::cout << "[>] Importing configuration: ";
    std::vector<std::unique_ptr<DeviceDescriptor>> d = DeviceDescriptor::from(argc > 1 ? argv[1] : "/home/luan/Documents/mqtt-mock-server/exemple.conf");
    std::cout << "OK" << std::endl;
    std::cout << "[>] " << d.size() << " devices detected" << std::endl;
    std::cout << "[>] Creating MetricGenerator: ";
    auto pMg = std::make_shared<MetricGenerator>();
    std::cout << "OK" << std::endl;

    ThreadDescriptor td = {};
    td.interval = std::chrono::seconds(2);

    std::cout << "[>] Creating ThreadController for each device: ";
    std::vector<ThreadController> tcs;
    for(auto& x : d) {
        tcs.emplace_back(std::make_unique<Device>(*x, pMg),td);
    }
    std::cout << "OK" << std::endl;

    std::cout << "[>] Starting threads" << std::endl;
    for(auto& x : tcs) {
        x.start();
    }
    if(!tcs.empty())
        tcs[0].join();

    return 0;
}