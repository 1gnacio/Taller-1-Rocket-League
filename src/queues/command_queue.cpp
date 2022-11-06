#include "command_queue.h"

CommandQueue::CommandQueue() : commands() {}

void CommandQueue::push(Command &command) {
    std::lock_guard<std::mutex> l(this->mutex);
    commands.push(std::move(command));
}

Command CommandQueue::pop() {
    std::lock_guard<std::mutex> l(this->mutex);
    if (!this->commands.empty()) {
        Command c = std::move(commands.front());
        commands.pop();
        return c;
    }

    // TODO que comando deberia devolver la cola si no hay comandos?
    return {0, "NOP"};
}