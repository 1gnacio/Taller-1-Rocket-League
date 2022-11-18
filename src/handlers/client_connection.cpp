#include <sys/socket.h>
#include "client_connection.h"

ClientConnection::ClientConnection(int id, Socket &socket, ResponseQueue &responseQueue, CommandQueue& commandQueue) :
isClosed(false),
socket(std::move(socket)),
helper(this->socket, id),
sender(this->socket, helper, responseQueue, SENDER),
receiver(this->socket, commandQueue, RECEIVER)
{}

void ClientConnection::push(Response &response) {
    this->isClosed = this->sender.isFinished();

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
        this->receiver.stopHandler();
        this->sender.stopHandler();
        this->socket.shutdown(SHUT_RDWR);
        this->socket.close();
        this->isClosed = true;
    }
}

ClientConnection::~ClientConnection() {
    if (!this->isClosed) {
        this->receiver.stopHandler();
        this->sender.stopHandler();
        this->socket.shutdown(SHUT_RDWR);
        this->socket.close();
        this->isClosed = true;
    }
}

