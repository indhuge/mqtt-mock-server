#pragma once
#include <memory>
#include <IExecutable.h>
#include <chrono>
#include <thread>
#include "Device.h"

struct ThreadDescriptor {
    std::chrono::seconds interval;
};

class ThreadController {
public:
    ThreadController() = delete;
    ThreadController(std::unique_ptr<IExecutable>&& object, ThreadDescriptor threadDescriptor);
    void start();
    void stop();
    void join();

private:
    std::unique_ptr<IExecutable> object;
    ThreadDescriptor threadDescriptor;
    std::thread thread;
};
