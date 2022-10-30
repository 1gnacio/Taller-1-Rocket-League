#include <netinet/in.h>
#include <algorithm>
#include <numeric>
#include "protocolo.h"

Protocolo::Protocolo() {}

void Protocolo::sendMovementResponse(Socket& socket,
                                     std::vector<std::string>
                                             performedMovement) {
    if (this->connectionClosed) {
        return;
    }

    std::string response = "";

    if (!performedMovement.empty()) {
        response = std::accumulate(
                std::next(performedMovement.begin()),
                performedMovement.end(),
                performedMovement.front(),
                [] (const std::string& a, const std::string& b)
                { return a + ", " + b; });
    }

    uint16_t responseSize = response.size();

    responseSize = htons(responseSize);

    socket.sendall(&responseSize, this->responseBytes, &this->connectionClosed);

    if (!this->connectionClosed) {
        socket.sendall(&response[0], response.size(), &this->connectionClosed);
    }
}

std::string Protocolo::receiveMovementResponse(Socket& socket) {
    std::string responseString;

    if (this->connectionClosed) {
        return responseString;
    }

    uint16_t responseSize;

    socket.recvall(&responseSize, this->responseBytes, &this->connectionClosed);

    if (!this->connectionClosed) {
        responseSize = ntohs(responseSize);

        std::vector<char> response(responseSize);

        socket.recvall(&response[0], responseSize, &this->connectionClosed);

        responseString = std::string(response.begin(), response.end());
    }

    return responseString;
}

std::vector<std::string> Protocolo::receiveCommands(Socket& socket) {
    std::vector<std::string> commands;

    if (this->connectionClosed) {
        return commands;
    }

    char serializedCommand;
    bool isFirstCommand = true;
    std::map<char, std::string> commandsMap = {
            {this->SERIALIZED_JUMP, this->DESERIALIZED_JUMP},
            {this->SERIALIZED_UP, this->DESERIALIZED_UP},
            {this->SERIALIZED_DOWN, this->DESERIALIZED_DOWN},
            {this->SERIALIZED_LEFT, this->DESERIALIZED_LEFT},
            {this->SERIALIZED_RIGHT, this->DESERIALIZED_RIGHT},
            {this->SERIALIZED_TURBO, this->DESERIALIZED_TURBO}
    };

    while (!this->connectionClosed
            && (isFirstCommand || !this->isEndOfCommands(serializedCommand))) {
        socket.recvall(&serializedCommand,
                       this->sentCommandsBytes,
                       &this->connectionClosed);

        if (!this->isEndOfCommands(serializedCommand)
            && !this->connectionClosed) {
            commands.push_back(commandsMap[serializedCommand]);
        }

        isFirstCommand = false;
    }

    return commands;
}

void Protocolo::sendCommands(Socket& socket,
                             std::vector<Command> commands) {
    if (this->connectionClosed) {
        return;
    }

    std::vector<char> serializedCommands(commands.size());

    std::transform(commands.begin(),
                   commands.end(),
                   serializedCommands.begin(),
                   [&commandsMap]
                   (Command command) {
                    return command.serialize();
    });

    socket.sendall(&serializedCommands[0],
                   serializedCommands.size(),
                   &this->connectionClosed);
}

bool Protocolo::isEndOfCommands(char serializedCommand) {
    return this->SERIALIZED_NOP == serializedCommand;
}

bool Protocolo::isConnectionClosed() {
    return this->connectionClosed;
}
