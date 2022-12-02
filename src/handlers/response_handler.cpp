#include "response_handler.h"
#include "../src/exceptions/socket_closed_exception.h"
#include "../src/exceptions/blocking_queue_closed_exception.h"

ResponseHandler::ResponseHandler(Socket &socket, IdService& idService, ResponseQueue &queue, Mode mode) :
        queue(queue),
        socket(socket),
        idService(idService),
        hasFinished(false),
        protocolo()
{
    if(mode == RECEIVER) {
        this->handler = std::thread(&ResponseHandler::handleReceive, this);
    } else if (mode == SENDER) {
        this->handler = std::thread(&ResponseHandler::handleSend, this);
    }
}

// hilo que recibe las respuestas del servidor
void ResponseHandler::handleReceive() {
    try {
        this->idService.run();

        while (!this->hasFinished) {
            Response r = protocolo.receiveResponse(this->socket);
            this->queue.push(r);
            this->hasFinished = protocolo.isConnectionClosed();
        }
    } catch (SocketClosedException &e) {
        this->hasFinished = true;
    }

}

// hilo que envia las respuestas del servidor
void ResponseHandler::handleSend() {
    try {
        this->idService.run();

        while (!this->hasFinished) {
            Response r = this->queue.pop();
            //TODO que deberia hacer el hilo si no recibe nada del servidor?
            protocolo.sendResponse(this->socket, r);
            this->hasFinished = protocolo.isConnectionClosed();
        }
    } catch (SocketClosedException &e) {
        this->hasFinished = true;
    } catch (BlockingQueueClosedException &e) {
        this->hasFinished = true;
    }
}

void ResponseHandler::push(Response &response) {
    if (!this->hasFinished) {
        this->queue.push(response);
    }
}

Response ResponseHandler::pop() {
    return this->queue.pop();
}

void ResponseHandler::stopHandler() {
    if (!this->hasFinished) {
        this->hasFinished = true;
    }
}

bool ResponseHandler::isFinished() {
    return this->hasFinished;
}

ResponseHandler::~ResponseHandler() {
    if (!this->hasFinished) {
        this->hasFinished = true;
    }

    this->handler.join();
}

void ResponseHandler::clearResponses() {
    this->queue.clearResponses();
}
