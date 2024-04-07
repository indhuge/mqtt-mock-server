#include "ThreadController.h"

ThreadController::ThreadController(std::unique_ptr<IExecutable>&& object, ThreadDescriptor threadDescriptor):
object(std::move(object)), threadDescriptor(threadDescriptor)
{
}

void ThreadController::start() {
    _isStarted = true;
    thread = std::thread([this] {
        while(true) {
            object->execute();
            std::this_thread::sleep_for(threadDescriptor.interval);
        }
    });
}

void ThreadController::stop() {
    if(isStarted()) {
        _isStarted = false;
        thread.detach();
    }
}

void ThreadController::join() {
    thread.join();
}

ThreadController::~ThreadController() {
    if(isStarted())
        thread.detach();
    object.release();
}

ThreadController::ThreadController(ThreadController&& threadController) noexcept {
    object = std::move(threadController.object);
    threadDescriptor = threadController.threadDescriptor;
    thread = std::move(threadController.thread);

    threadController.object = nullptr;
}

bool ThreadController::isStarted() const {
    return _isStarted;
}
