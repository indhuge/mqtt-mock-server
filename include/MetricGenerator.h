#pragma once
#include <random>

class MetricGenerator {
public:
    MetricGenerator();

    double generatePressure();
    int generateTemperature();
    int generateRpm();

private:
    std::random_device randomDevice;
    std::mt19937 mt;
    std::uniform_real_distribution<double> d_pressure;
    std::uniform_int_distribution<int> d_temperature;
    std::uniform_int_distribution<int> d_rpm;

};
