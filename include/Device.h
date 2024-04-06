#pragma once
#include <DeviceDescriptor.h>

class Device {
public:
    Device() = delete;
    Device(DeviceDescriptor deviceDescriptor);



private:
    DeviceDescriptor descriptor;
    MqttConnection mqttConnection;
};
