#include <sys/socket.h>
#include "server_connection.h"

ServerConnection::ServerConnection(Socket &socket) :
isConnected(true),
socket(std::move(socket)),
commandQueue(),
sender(this->socket, this->commandQueue, SENDER),
receiver(this->socket, RECEIVER)
{}

void ServerConnection::push(Command &command) {
    this->isConnected = !this->sender.isFinished() && !this->receiver.isFinished();

    if(this->isConnected) {
        this->commandQueue.push(command);
    }
}

Response ServerConnection::pop() {
    return this->receiver.pop();
}

bool ServerConnection::connectionClosed() {
    return !this->isConnected;
}

void ServerConnection::closeConnection() {
    if(!this->isConnected) {
        this->socket.shutdown(SHUT_RDWR);
        this->socket.close();
        this->sender.stopHandler();
        this->receiver.stopHandler();
        this->isConnected = false;
    }
}

ServerConnection::~ServerConnection() {
    if(!this->isConnected) {
        this->socket.shutdown(SHUT_RDWR);
        this->socket.close();
        this->sender.stopHandler();
        this->receiver.stopHandler();
        this->isConnected = false;
    }
}
