#include <sys/socket.h>
#include <iostream>
#include "server_connection.h"
#include "../src/sockets/liberror.h"

ServerConnection::ServerConnection(const char *hostname, const char *servname) :
isConnected(true),
socket(hostname, servname),
idService(RECEIVER, socket, 0),
commandQueue(),
sender(this->socket, this->commandQueue, SENDER),
receiver(this->socket, idService, this->responseQueue, RECEIVER)
{}

void ServerConnection::push(Command &command) {
    if(!this->sender.isFinished()) {
        this->commandQueue.push(command);
    }
}

Response ServerConnection::pop() {
    return this->receiver.pop();
}

bool ServerConnection::connectionClosed() {
    return this->sender.isFinished() || this->receiver.isFinished();
}

void ServerConnection::closeConnection() {
    if(this->isConnected) {
        this->commandQueue.close();
        try {
            this->socket.shutdown(SHUT_RDWR);
        } catch (LibError &e) {
            if (errno == ENOTCONN) {
                std::cout << "La conexion con el servidor ha terminado de forma repentina. "
                             "Posiblemente el servidor se encuentre desconectado." << std::endl;
            } else {
                std::cout << e.what() << std::endl;
            }
        }
        this->socket.close();
        this->sender.stopHandler();
        this->receiver.stopHandler();
        this->isConnected = false;
    }
}

ServerConnection::~ServerConnection() {
    if(this->isConnected) {
        this->commandQueue.close();
        try {
            this->socket.shutdown(SHUT_RDWR);
        } catch (LibError &e) {
            if (errno == ENOTCONN) {
                std::cout << "La conexion con el servidor ha terminado de forma repentina. "
                             "Posiblemente el servidor se encuentre desconectado." << std::endl;
            }
        }
        this->socket.close();
        this->sender.stopHandler();
        this->receiver.stopHandler();
        this->isConnected = false;
    }
}

void ServerConnection::setConnectedGameName(const std::string &name) {
    this->gameName = name;
}

void ServerConnection::clearGameName() {
    this->gameName.clear();
}

void ServerConnection::clearResponses() {
    this->receiver.clearResponses();
}


