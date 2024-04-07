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
    ThreadController(ThreadController& threadController) = delete;
    ThreadController(ThreadController&& threadController) noexcept ;
    ThreadController(std::unique_ptr<IExecutable>&& object, ThreadDescriptor threadDescriptor);
    ~ThreadController();
    void start();
    void stop();
    void join();
    bool isStarted() const;

private:
    bool _isStarted = false;
    std::unique_ptr<IExecutable> object;
    ThreadDescriptor threadDescriptor;
    std::thread thread;
};
