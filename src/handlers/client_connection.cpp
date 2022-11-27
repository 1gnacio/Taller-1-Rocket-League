#include <sys/socket.h>
#include "client_connection.h"

ClientConnection::ClientConnection(int id, CommandQueue& queue, Socket &socket) :
isClosed(false),
socket(std::move(socket)),
idService(SENDER, this->socket, id),
commandQueue(queue),
responseQueue(),
sender(this->socket, idService, responseQueue, SENDER),
receiver(this->socket, commandQueue, RECEIVER)
{}

void ClientConnection::push(Response &response) {
    this->isClosed = this->sender.isFinished() || this->receiver.isFinished();

    if (!this->isClosed) {
        this->sender.push(response);
    }
}

bool ClientConnection::connectionClosed() {
    this->isClosed = this->sender.isFinished() || this->receiver.isFinished();
    return this->isClosed;
}

void ClientConnection::closeConnection() {
    if (!this->isClosed) {
        this->responseQueue.close();
        this->receiver.stopHandler();
        this->sender.stopHandler();
        this->socket.shutdown(SHUT_RDWR);
        this->socket.close();
        this->isClosed = true;
    }
}

ClientConnection::~ClientConnection() {
    if (!this->isClosed) {
        this->responseQueue.close();
        this->receiver.stopHandler();
        this->sender.stopHandler();
        this->socket.shutdown(SHUT_RDWR);
        this->socket.close();
        this->isClosed = true;
    }
}

