#include "Device.h"

Device::Device(DeviceDescriptor deviceDescriptor) :
descriptor(deviceDescriptor),
mqttConnection(
        deviceDescriptor.connectionConfig.host,
        std::stoi(deviceDescriptor.connectionConfig.port),
        deviceDescriptor.tlsConfig){}
