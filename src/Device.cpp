#include "Device.h"
#include <nlohmann/json.hpp>
#include <iostream>
#include <thread>

Device::Device(DeviceDescriptor deviceDescriptor, std::shared_ptr<MetricGenerator> metricGenerator) :
descriptor(deviceDescriptor),
metricGenerator(std::move(metricGenerator)),
mqttConnection(
        deviceDescriptor.connectionConfig.host,
        std::stoi(deviceDescriptor.connectionConfig.port),
        deviceDescriptor.tlsConfig){}

void Device::generateMessage() {
    nlohmann::json j;
    j["temperature"] = temperature + metricGenerator->generateTemperature();
    j["pressure"] = pressure + metricGenerator->generatePressure();
    j["rpm"] = rpm + metricGenerator->generateRpm();
    j["type"] = descriptor.type;
    j["device_id"] = descriptor.device_id;

    // mqttConnection.publish(descriptor.topic, to_string(j));
    std::cout << descriptor.topic << " -> " << j << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(2));
}

