#include <netinet/in.h>
#include <algorithm>
#include <numeric>
#include "protocolo.h"

Protocolo::Protocolo() {}

//void Protocolo::sendMovementResponse(Socket& socket,
//                                     std::vector<std::string>
//                                             performedMovement) {
//    if (this->connectionClosed) {
//        return;
//    }
//
//    std::string response = "";
//
//    if (!performedMovement.empty()) {
//        response = std::accumulate(
//                std::next(performedMovement.begin()),
//                performedMovement.end(),
//                performedMovement.front(),
//                [] (const std::string& a, const std::string& b)
//                { return a + ", " + b; });
//    }
//
//    uint16_t responseSize = response.size();
//
//    responseSize = htons(responseSize);
//
//    socket.sendall(&responseSize, this->responseBytes, &this->connectionClosed);
//
//    if (!this->connectionClosed) {
//        socket.sendall(&response[0], response.size(), &this->connectionClosed);
//    }
//}

void Protocolo::sendResponse(Response &response) {
    //TODO enviar respuesta a todos los clientes
}

Command Protocolo::receiveCommand() {
    //TODO hacer pop de la lista de comandos recibidos
}

void Protocolo::sendCommand(Socket &socket, Command &command) {
    if (this->connectionClosed) {
        return;
    }

    std::vector<char> serializedCommand(command.serialize());

    socket.sendall(&serializedCommand[0],
                   1,
                   &this->connectionClosed);
}

Response Protocolo::receiveResponse(Socket &socket) {
    if (this->connectionClosed) {
        // TODO: definir comportamiento cuando se cierra la conexion antes de recibir respuesta
        return Response(std::vector<char>());
    }

    std::vector<char> serializedResponse;

    uint16_t responseSize;

    socket.recvsome(&responseSize,
                   2,
                   &this->connectionClosed);

    if (!this->connectionClosed) {
        socket.recvall(&serializedResponse,
                        responseSize,
                        &this->connectionClosed);
    }

    return Response(serializedResponse);
}

bool Protocolo::isEndOfCommands(char serializedCommand) {
    CommandValues values;
    return values.SERIALIZED_NOP == serializedCommand;
}

bool Protocolo::isConnectionClosed() {
    return this->connectionClosed;
}
