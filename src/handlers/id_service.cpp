#include "id_service.h"
#include "src/protocolo/protocolo.h"

IdService::IdService(Mode mode, Socket &socket, int id) : mode(mode), socket(socket), id(id) {}

void IdService::sendId() {
    for (int i = 0; i < 3; ++i) {
        Protocolo().sendId(this->socket, this->id);
    }
}

void IdService::receiveId() {
    for (int i = 0; i < 3; ++i) {
        this->id = Protocolo().receiveId(socket);
    }
}

void IdService::run() {
    if (this->mode == SENDER) {
        this->sendId();
    } else {
        this->receiveId();
    }
}

