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
    //
    //  -> podes hacer q el pop sea bloqueante y nunca retorne
    //  -> podes hacer el pop no-bloqueante y q retorne un dummy como
    //  lo estas haciendo aca
    return {0, 0, "NOP"};
}

// Esto SOLO te trae problemas por q ahora si 2 hilos acceden a commands
// y uno llama a isEmpty va a estar accediendo a un recurso compartido
// sin proteccion.
// Esto SOLO te trae Race Conditions
bool CommandQueue::isEmpty() {
    return commands.empty();
}
