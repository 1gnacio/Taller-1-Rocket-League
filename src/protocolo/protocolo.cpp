#include <netinet/in.h>
#include <algorithm>
#include <numeric>
#include "protocolo.h"

Protocolo::Protocolo() {}

void Protocolo::sendResponse(Socket& socket, Response &response) {
    //TODO enviar respuesta a todos los clientes
}

Command Protocolo::receiveCommand(Socket& socket) {
    if (this->isConnectionClosed()) {
        return {0, "NOP"};
    }

    uint16_t responseSize;

    socket.recvall(&responseSize, this->responseBytes, &this->connectionClosed);

    if (!this->connectionClosed) {
        responseSize = ntohs(responseSize);

        std::vector<char> serializedCommand(responseSize);

        socket.recvall(&serializedCommand[0], responseSize, &this->connectionClosed);

        return ProtocolCommands().createCommand(serializedCommand);
    }

    return {0, "NOP"};
}

void Protocolo::sendCommand(Socket &socket, Command &command) {
    if (this->connectionClosed) {
        return;
    }

    std::vector<char> serializedCommand;

    serializedCommand.push_back(command.serialize());

    uint16_t responseSize = serializedCommand.size();

    responseSize = htons(responseSize);

    socket.sendall(&responseSize, this->responseBytes, &this->connectionClosed);

    if (!this->connectionClosed) {
        socket.sendall(&serializedCommand[0], serializedCommand.size(), &this->connectionClosed);
    }
}

Response Protocolo::receiveResponse(Socket &socket) {
    if (this->connectionClosed) {
        // TODO: definir comportamiento cuando se cierra la conexion antes de recibir respuesta
        return Response(std::vector<char>());
    }

    uint16_t responseSize;

    socket.recvall(&responseSize, this->responseBytes, &this->connectionClosed);

    if (!this->connectionClosed) {
        responseSize = ntohs(responseSize);

        std::vector<char> serializedResponse(responseSize);

        socket.recvall(&serializedResponse[0], responseSize, &this->connectionClosed);
    }

    return {"ERROR", "NO IMPLEMENTADO"};
}

bool Protocolo::isEndOfCommands(char serializedCommand) {
    CommandValues values;
    return values.SERIALIZED_NOP == serializedCommand;
}

bool Protocolo::isConnectionClosed() {
    return this->connectionClosed;
}
