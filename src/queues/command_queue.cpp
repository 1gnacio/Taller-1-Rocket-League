#include "command_queue.h"

CommandQueue::CommandQueue() : commands(), protocolo() {}

void CommandQueue::push(Command &command) {
    commands.push(std::move(command));
}

Command CommandQueue::pop() {
    if (!this->commands.empty()) {
        Command c = std::move(commands.front());
        commands.pop();
        return c;
    }

    // TODO que comando deberia devolver la cola si no hay comandos?
    return Command('0', "NOP");
}