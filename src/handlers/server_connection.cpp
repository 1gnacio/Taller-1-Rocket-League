#include <sys/socket.h>
#include "server_connection.h"

ServerConnection::ServerConnection(const char *hostname, const char *servname) :
isConnected(true),
socket(hostname, servname),
idService(RECEIVER, socket, 0),
commandQueue(),
sender(this->socket, this->commandQueue, SENDER),
receiver(this->socket, idService, this->responseQueue, RECEIVER)
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
        std::string value = CommandValues().DESERIALIZED_QUIT_GAME;
        Command c = ProtocolCommands().createCommand(this->idService.getId(), value);
        this->commandQueue.push(c);
        this->commandQueue.close();
        this->socket.shutdown(SHUT_RDWR);
        this->socket.close();
        this->sender.stopHandler();
        this->receiver.stopHandler();
        this->isConnected = false;
    }
}

ServerConnection::~ServerConnection() {
    if(this->isConnected) {
        std::string value = CommandValues().DESERIALIZED_QUIT_GAME;
        Command c = ProtocolCommands().createCommand(this->idService.getId(), value);
        this->commandQueue.push(c);
        this->commandQueue.close();
        this->socket.shutdown(SHUT_RDWR);
        this->socket.close();
        this->sender.stopHandler();
        this->receiver.stopHandler();
        this->isConnected = false;
    }
}

void ServerConnection::setConnectedGameName(std::string &name) {
    this->gameName = name;
}

void ServerConnection::clearGameName() {
    this->gameName.clear();
}


