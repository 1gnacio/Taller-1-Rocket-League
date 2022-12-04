#include <netinet/in.h>
#include <algorithm>
#include "protocolo.h"
#include "../constants/response_values.h"
#include "../src/sockets/liberror.h"
#include "../src/exceptions/socket_closed_exception.h"

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
    try {
        if (this->connectionClosed) {
            return;
        }

        std::vector<unsigned char> serialized = response.serialize();

        this->sendMessage(socket, serialized);
    } catch (LibError& e) {
        if (errno == ECONNRESET) {
            this->connectionClosed = true;
            throw SocketClosedException(e);
        }
        throw e;
    }
}

Command Protocolo::receiveCommand(Socket& socket) {
    try {
        if (this->connectionClosed) {
            CommandValues cv;
            return {0, cv.SERIALIZED_NOP, cv.DESERIALIZED_NOP};
        }

        std::vector<unsigned char> message = this->receiveMessage(socket);

        Command receivedCommand(message);

        return receivedCommand;
    } catch (LibError& e) {
        if (errno == ECONNRESET) {
            this->connectionClosed = true;
            throw SocketClosedException(e);
        }
        throw e;
    }
}



void Protocolo::sendCommand(Socket &socket, Command &command) {
    try {
        if (this->connectionClosed) {
            return;
        }

        std::vector<unsigned char> serializedCommand = command.serialize();

        this->sendMessage(socket, serializedCommand);
    } catch (LibError& e) {
        if (errno == ECONNRESET) {
            this->connectionClosed = true;
            throw SocketClosedException(e);
        }
        throw e;
    }
}

Response Protocolo::receiveResponse(Socket &socket) {
    try {
        if (this->connectionClosed) {
            ActionResultResponse actionResponse(ResponseValues().ERROR, ResponseValues().CONNECTION_CLOSED);
            LobbyResponse lobby(actionResponse);
            return std::move(Response(lobby));
        }

        std::vector<unsigned char> message = this->receiveMessage(socket);

        return std::move(Response(message));
    } catch (LibError& e) {
        if (errno == ECONNRESET) {
            this->connectionClosed = true;
            throw SocketClosedException(e);
        }
        throw e;
    }
}

bool Protocolo::isConnectionClosed() {
    return this->connectionClosed;
}

void Protocolo::sendId(Socket &socket, int id) {
    try {
        if (this->connectionClosed) {
            return;
        }
        std::vector<unsigned char> serializedId = Serializer().serializeInt(id);

        this->sendMessage(socket, serializedId);
    } catch (LibError& e) {
        if (errno == ECONNRESET) {
            this->connectionClosed = true;
            throw SocketClosedException(e);
        }
        throw e;
    }
}

int Protocolo::receiveId(Socket &socket) {
    try {
        if (this->connectionClosed) {
            return 0;
        }

        std::vector<unsigned char> serializedInt = this->receiveMessage(socket);

        return serializedInt.size() > 0 ? Serializer().deserializeInt(serializedInt) : 0;
    } catch (LibError& e) {
        if (errno == ECONNRESET) {
            this->connectionClosed = true;
            throw SocketClosedException(e);
        }
        throw e;
    }
}
