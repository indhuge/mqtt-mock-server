//
// Created by luan on 4/6/24.
//

#include "MetricGenerator.h"

MetricGenerator::MetricGenerator() :
d_pressure(-10, 10), d_temperature(-5, 5), d_rpm(-1, 1), mt(randomDevice()) {}

double MetricGenerator::generatePressure() {
    return d_pressure(mt);
}

int MetricGenerator::generateTemperature() {
    return d_temperature(mt);
}

int MetricGenerator::generateRpm() {
    return d_rpm(mt);
}
