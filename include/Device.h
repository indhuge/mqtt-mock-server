#pragma once
#include <DeviceDescriptor.h>
#include <MetricGenerator.h>
#include <IExecutable.h>

class Device : public IExecutable {
public:
    Device() = delete;
    Device(DeviceDescriptor deviceDescriptor, std::shared_ptr<MetricGenerator> metricGenerator);

    void generateMessage();
    void execute() override;
private:
    DeviceDescriptor descriptor;
    MqttConnection mqttConnection;
    std::shared_ptr<MetricGenerator> metricGenerator;

    double temperature = 20.0;
    double pressure = 2.338;
    int rpm = 600;
};
