#include <sys/socket.h>
#include "response_handler.h"

ResponseHandler::ResponseHandler(Socket& socket, Mode mode) :
queue(),
socket(std::move(socket)),
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
    while (!this->hasFinished) {
        Response r = protocolo.receiveResponse(this->socket);
        this->queue.push(r);
        this->hasFinished = protocolo.isConnectionClosed();
    }
}

// hilo que envia las respuestas del servidor
void ResponseHandler::handleSend() {
    while (!this->hasFinished) {
        Response r = this->queue.pop();
        //TODO que deberia hacer el hilo si no recibe nada del servidor?
        protocolo.sendResponse(this->socket, r);
        this->hasFinished = protocolo.isConnectionClosed();
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
        this->socket.shutdown(SHUT_RDWR);
        this->socket.close();
    }
}

ResponseHandler::~ResponseHandler() {
    if (!this->hasFinished) {
        this->hasFinished = true;
        this->socket.shutdown(SHUT_RDWR);
        this->socket.close();
    }

    this->handler.join();
}