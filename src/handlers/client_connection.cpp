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
    if (!this->sender.isFinished()) {
        this->sender.push(response);
    }
}

bool ClientConnection::connectionClosed() {
    return this->sender.isFinished() || this->receiver.isFinished();
}

void ClientConnection::closeConnection() {
    if (!this->isClosed) {
        this->responseQueue.close();
        this->socket.shutdown(SHUT_RDWR);
        this->socket.close();
        this->receiver.stopHandler();
        this->sender.stopHandler();
        this->isClosed = true;
    }
}

ClientConnection::~ClientConnection() {
    if (!this->isClosed) {
        this->responseQueue.close();
        this->socket.shutdown(SHUT_RDWR);
        this->socket.close();
        this->receiver.stopHandler();
        this->sender.stopHandler();
        this->isClosed = true;
    }
}

