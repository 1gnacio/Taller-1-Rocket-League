#include <sys/socket.h>
#include "client_connection.h"

ClientConnection::ClientConnection(Socket &socket, CommandQueue& queue) :
socket(std::move(socket)),
sender(this->socket, SENDER),
receiver(this->socket, queue, RECEIVER)
{}

void ClientConnection::push(Response &response) {
    if (!this->isClosed) {
        this->sender.push(response);
    }
}

bool ClientConnection::connectionClosed() {
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

