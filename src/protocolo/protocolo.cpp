#include <netinet/in.h>
#include <algorithm>
#include "protocolo.h"
#include "../constants/response_values.h"
#include "../src/sockets/liberror.h"
#include "../src/exceptions/socket_closed_exception.h"

Protocolo::Protocolo() {}

void Protocolo::receiveResponseSize(Socket &socket, uint16_t &responseSize) {
    try {
        socket.recvall(&responseSize, this->responseBytes, &this->connectionClosed);
    } catch (LibError& e) {
        if (errno == EPIPE || errno == EBADF) {
            this->connectionClosed = true;
            throw SocketClosedException(e);
        }
        throw e;
    }
}

void Protocolo::sendResponseSize(Socket &socket, uint16_t responseSize) {
    try {
        socket.sendall(&responseSize, this->responseBytes, &this->connectionClosed);
    } catch (LibError& e) {
        if (errno == EPIPE || errno == EBADF) {
            this->connectionClosed = true;
            throw SocketClosedException(e);
        }
        throw e;
    }
}

void Protocolo::sendAll(Socket &socket, std::vector<unsigned char> &message) {
    try {
        socket.sendall(&message[0], message.size(), &this->connectionClosed);
    } catch (LibError& e) {
        if (errno == EPIPE || errno == EBADF) {
            this->connectionClosed = true;
            throw SocketClosedException(e);
        }
        throw e;
    }
}

void Protocolo::receiveAll(Socket &socket, std::vector<unsigned char> &message, uint16_t responseSize) {
    try {
        socket.recvall(&message[0], responseSize, &this->connectionClosed);
    } catch (LibError& e) {
        if (errno == EPIPE || errno == EBADF) {
            this->connectionClosed = true;
            throw SocketClosedException(e);
        }
        throw e;
    }
}

void Protocolo::sendMessage(Socket& socket, std::vector<unsigned char> &message) {
    uint16_t responseSize = message.size();

    responseSize = htons(responseSize);

    this->sendResponseSize(socket, responseSize);

    if (!this->connectionClosed) {
        this->sendAll(socket, message);
    }
}

std::vector<unsigned char> Protocolo::receiveMessage(Socket &socket) {
    uint16_t responseSize;

    this->receiveResponseSize(socket, responseSize);

    if (!this->connectionClosed) {
        responseSize = ntohs(responseSize);

        std::vector<unsigned char> serializedResponse(responseSize);

        this->receiveAll(socket, serializedResponse, responseSize);

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
    if (this->connectionClosed) {
        CommandValues cv;
        return {0, cv.SERIALIZED_NOP, cv.DESERIALIZED_NOP};
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
        ActionResultResponse actionResponse(ResponseValues().ERROR, ResponseValues().CONNECTION_CLOSED);
        LobbyResponse lobby(actionResponse);
        return {lobby};
    }

    std::vector<unsigned char> message = this->receiveMessage(socket);

    return {message};
}

bool Protocolo::isConnectionClosed() {
    return this->connectionClosed;
}

void Protocolo::sendId(Socket &socket, int id) {
    if (this->connectionClosed) {
        return;
    }
    std::vector<unsigned char> serializedId = Serializer().serializeInt(id);

    this->sendMessage(socket, serializedId);
}

int Protocolo::receiveId(Socket &socket) {
    if (this->connectionClosed) {
        return 0;
    }

    std::vector<unsigned char> serializedInt = this->receiveMessage(socket);

    return !serializedInt.empty() ? Serializer().deserializeInt(serializedInt) : 0;
}
