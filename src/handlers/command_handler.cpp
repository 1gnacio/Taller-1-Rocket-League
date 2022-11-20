#include "command_handler.h"
#include "../src/exceptions/blocking_queue_closed_exception.h"

CommandHandler::CommandHandler(Socket &socket, CommandQueue& queue, Mode mode) :
hasFinished(false),
queue(queue),
protocolo(),
socket(socket)
{
    if (mode == RECEIVER) {
        this->handler = std::thread(&CommandHandler::handleReceive, this);
    } else if (mode == SENDER) {
        this->handler = std::thread(&CommandHandler::handleSend, this);
    }
}

void CommandHandler::handleSend() {
    while (!this->hasFinished) {
        try {
            Command element = this->queue.pop();
            protocolo.sendCommand(this->socket, element);
        } catch (const BlockingQueueClosedException &ex) {
            this->hasFinished = true;
        } catch (std::exception &ex) {
            this->hasFinished = true;
        }
    }
}

void CommandHandler::handleReceive() {
    try {
        while (!this->hasFinished) {
            Command c = protocolo.receiveCommand(this->socket);
            this->hasFinished = this->protocolo.isConnectionClosed();
            this->queue.push(c);
        }
    } catch (std::exception &e) {
        this->hasFinished = true;
    }
}

void CommandHandler::push(Command &command) {
    if (!this->hasFinished) {
        this->queue.push(command);
    }
}

Command CommandHandler::pop() {
    try {
        return this->queue.pop();
    } catch (const BlockingQueueClosedException &ex) {
        this->hasFinished = true;
    }
}

void CommandHandler::stopHandler() {
    if (!this->hasFinished) {
        this->hasFinished = true;
    }
}

bool CommandHandler::isFinished() {
    return this->hasFinished;
}

CommandHandler::~CommandHandler() {
    if (!this->hasFinished) {
        this->hasFinished = true;
    }

    this->handler.join();
}
