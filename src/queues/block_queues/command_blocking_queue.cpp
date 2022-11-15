#include "command_blocking_queue.h"

void CommandBlockingQueue::push(Command &element) {
    std::unique_lock<std::mutex> lock(mutex);
    this->commands.push(std::move(element));
    cv.notify_all();
}

Command CommandBlockingQueue::pop() {
    std::unique_lock<std::mutex> lock(mutex);
    while(this->commands.empty()) {
        cv.wait(lock);
    }
    Command element = std::move(this->commands.front());
    this->commands.pop();
    return std::move(element);
}