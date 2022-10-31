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

std::vector<Command> Protocolo::receiveCommands(Socket& socket) {
    std::vector<std::string> commands;

    if (this->connectionClosed) {
        return commands;
    }

    char serializedCommand;
    bool isFirstCommand = true;

    while (!this->connectionClosed
            && (isFirstCommand || !this->isEndOfCommands(serializedCommand))) {
        socket.recvall(&serializedCommand,
                       this->sentCommandsBytes,
                       &this->connectionClosed);

        if (!this->isEndOfCommands(serializedCommand)
            && !this->connectionClosed) {
            commands.push_back(this->protocolCommands.createMovementCommand(serializedCommand));
        }

        isFirstCommand = false;
    }

    return commands;
}

std::vector<char> Protocolo::serializeMovementCommands(std::vector <Command> &commands) {
    std::vector<char> serializedCommands(commands.size());

    std::transform(commands.begin(),
                   commands.end(),
                   serializedCommands.begin(),
                   [&commands]
                           (Command& command) {
                       return command.serialize();
                   });

    return serializedCommands;
}

void Protocolo::sendCommands(Socket& socket,
                             std::vector<Command> commands) {
    if (this->connectionClosed) {
        return;
    }

    std::vector<char> serializedCommands = this->serializeMovementCommands(commands);

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
