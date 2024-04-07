#pragma once
#include <DeviceDescriptor.h>
#include <MetricGenerator.h>

class Device {
public:
    Device() = delete;
    Device(DeviceDescriptor deviceDescriptor, std::shared_ptr<MetricGenerator> metricGenerator);

    void generateMessage();


private:
    DeviceDescriptor descriptor;
    MqttConnection mqttConnection;
    std::shared_ptr<MetricGenerator> metricGenerator;

    double temperature = 20.0;
    double pressure = 2.338;
    int rpm = 600;
};
