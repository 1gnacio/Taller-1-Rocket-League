#include <sys/socket.h>
#include "server_connection.h"

ServerConnection::ServerConnection(const char *hostname, const char *servname) :
isConnected(true),
socket(hostname, servname),
helper(socket),
commandQueue(),
sender(this->socket, this->commandQueue, SENDER),
receiver(this->socket, helper, this->responseQueue, RECEIVER)
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
    if(this->isConnected) {
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
