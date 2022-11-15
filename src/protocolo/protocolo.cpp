#include <netinet/in.h>
#include <algorithm>
#include <numeric>
#include "protocolo.h"
#include <csignal>

Protocolo::Protocolo() {}

void Protocolo::sendMessage(Socket& socket, std::vector<unsigned char> &message) {
    uint16_t responseSize = message.size();

    responseSize = htons(responseSize);

    socket.sendall(&responseSize, this->responseBytes, &this->connectionClosed);

    if (!this->connectionClosed) {
        socket.sendall(&message[0], message.size(), &this->connectionClosed);
    }
}

std::vector<unsigned char> Protocolo::receiveMessage(Socket &socket) {
    uint16_t responseSize;

    socket.recvall(&responseSize, this->responseBytes, &this->connectionClosed);

    if (!this->connectionClosed) {
        responseSize = ntohs(responseSize);

        std::vector<unsigned char> serializedResponse(responseSize);

        socket.recvall(&serializedResponse[0], responseSize, &this->connectionClosed);

        return serializedResponse;
    }

    return {};
}

void Protocolo::sendResponse(Socket& socket, Response &response) {
    if (this->connectionClosed) {
        return;
    }

    std::vector<unsigned char> serialized = response.serialize();

    this->sendMessage(socket, serialized);
}

Command Protocolo::receiveCommand(Socket& socket) {
    if (this->isConnectionClosed()) {
        CommandValues cv;
        return {cv.SERIALIZED_NOP, cv.DESERIALIZED_NOP};
    }

    std::vector<unsigned char> message = this->receiveMessage(socket);

    Command receivedCommand(message);

    return receivedCommand;
}



void Protocolo::sendCommand(Socket &socket, Command &command) {
    if (this->connectionClosed) {
        return;
    }

    std::vector<unsigned char> serializedCommand = command.serialize();

    this->sendMessage(socket, serializedCommand);
}

Response Protocolo::receiveResponse(Socket &socket) {
    if (this->connectionClosed) {
        return {"ERROR", "CONEXION CERRADA"};
    }

    std::vector<unsigned char> message = this->receiveMessage(socket);

    return {message};
}

bool Protocolo::isConnectionClosed() {
    return this->connectionClosed;
}
