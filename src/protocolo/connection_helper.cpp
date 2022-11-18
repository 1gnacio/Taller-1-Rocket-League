#include "connection_helper.h"
#include "protocolo.h"

ConnectionHelper::ConnectionHelper(Socket &socket)
: hasFinished(false), idManager(&ConnectionHelper::receiveId, this, std::ref(socket)) {}

ConnectionHelper::ConnectionHelper(Socket &socket, int id)
: hasFinished(false), id(id), idManager(&ConnectionHelper::sendId, this, std::ref(socket), std::ref(id)) {}

void ConnectionHelper::sendId(Socket &socket, int clientId) {
    Protocolo().sendId(socket, clientId);
}

void ConnectionHelper::receiveId(Socket &socket) {
    this->id = Protocolo().receiveId(socket);
}

void ConnectionHelper::awaitHelper() {
    if (!this->hasFinished) {
        this->idManager.join();
        this->hasFinished = true;
    }
}

ConnectionHelper::~ConnectionHelper() {
    if (!this->hasFinished) {
        this->idManager.join();
        this->hasFinished = true;
    }
}


