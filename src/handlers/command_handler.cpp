#include <sys/socket.h>
#include "command_handler.h"

CommandHandler::CommandHandler(Socket &socket, CommandQueue& queue, Mode mode) :
hasFinished(false),
queue(queue),
protocolo(),
socket(std::move(socket)) {
    if (mode == RECEIVER) {
        this->handler = std::thread(&CommandHandler::handleReceive, this);
    } else if (mode == SENDER) {
        this->handler = std::thread(&CommandHandler::handleSend, this);
    }
}

void CommandHandler::handleSend() {
    while (!this->hasFinished) {
        Command c = this->queue.pop();
        protocolo.sendCommand(this->socket, c);
        this->hasFinished = this->protocolo.isConnectionClosed();
    }
}

void CommandHandler::handleReceive() {
    while (!this->hasFinished) {
        Command c = protocolo.receiveCommand(this->socket);
        this->hasFinished = this->protocolo.isConnectionClosed();
        this->queue.push(c);
    }
}

void CommandHandler::push(Command &command) {
    if (!this->hasFinished) {
        this->queue.push(command);
    }
}

Command CommandHandler::pop() {
    return this->queue.pop();
}

void CommandHandler::stopHandler() {
    if (!this->hasFinished) {
        this->hasFinished = true;
        this->socket.shutdown(SHUT_RDWR);
        this->socket.close();
    }
}

bool CommandHandler::isFinished() {
    return this->hasFinished;
}

CommandHandler::~CommandHandler() {
    if (!this->hasFinished) {
        this->hasFinished = true;
        this->socket.shutdown(SHUT_RDWR);
        this->socket.close();
    }

    this->handler.join();
}
