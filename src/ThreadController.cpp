#include "ThreadController.h"

ThreadController::ThreadController(std::unique_ptr<IExecutable>&& object, ThreadDescriptor threadDescriptor):
object(std::move(object)), threadDescriptor(threadDescriptor)
{
}

void ThreadController::start() {
    thread = std::thread([this] {
        while(true) {
            object->execute();
            std::this_thread::sleep_for(threadDescriptor.interval);
        }
    });
}

void ThreadController::stop() {
    thread.detach();
}

void ThreadController::join() {
    thread.join();
}