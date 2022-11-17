#include "connection_helper.h"
#include "protocolo.h"

ConnectionHelper::ConnectionHelper(Socket &socket) : id(this->receiveId(socket)) {}

ConnectionHelper::ConnectionHelper(Socket &socket, int id) : id(id) {
    this->sendId(socket);
}

void ConnectionHelper::sendId(Socket &socket) {
    Protocolo().sendId(socket, this->id);
}

int ConnectionHelper::receiveId(Socket &socket) {
    return Protocolo().receiveId(socket);
}
