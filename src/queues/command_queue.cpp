#include "command_queue.h"

CommandQueue::CommandQueue() : commands() {}

void CommandQueue::push(Command &command) {
    std::lock_guard<std::mutex>(this->mutex);
    commands.push(std::move(command));
}

Command CommandQueue::pop() {
    std::lock_guard<std::mutex>(this->mutex);
    if (!this->commands.empty()) {
        Command c = std::move(commands.front());
        commands.pop();
        return c;
    }

    // TODO que comando deberia devolver la cola si no hay comandos?
    return Command('0', "NOP");
}