#include <sys/socket.h>
#include <iostream>
#include "client_connection.h"
#include "../src/sockets/liberror.h"

ClientConnection::ClientConnection(int id, CommandQueue& queue, Socket &socket) :
isClosed(false),
socket(std::move(socket)),
idService(SENDER, this->socket, id),
commandQueue(queue),
responseQueue(),
sender(this->socket, idService, responseQueue, SENDER),
receiver(this->socket, commandQueue, RECEIVER)
{}

void ClientConnection::push(Response &response) {
    if (!this->sender.isFinished()) {
        this->sender.push(response);
    }
}

bool ClientConnection::connectionClosed() {
    return this->sender.isFinished() || this->receiver.isFinished();
}

void ClientConnection::closeConnection() {
    if (!this->isClosed) {
        this->responseQueue.close();
        try {
            this->socket.shutdown(SHUT_RDWR);
        } catch (LibError &e) {
            if (errno == ENOTCONN) {
                std::cout << "La conexion con el cliente ha terminado de forma repentina. "
                             "Posiblemente el cliente haya terminado la conexion de forma abrupta." << std::endl;
            } else {
                std::cout << e.what() << std::endl;
            }
        }
        this->socket.close();
        this->receiver.stopHandler();
        this->sender.stopHandler();
        this->isClosed = true;
    }
}

ClientConnection::~ClientConnection() {
    if (!this->isClosed) {
        this->responseQueue.close();
        try {
            this->socket.shutdown(SHUT_RDWR);
        } catch (LibError &e) {
            if (errno == ENOTCONN) {
                std::cout << "La conexion con el cliente ha terminado de forma repentina. "
                             "Posiblemente el cliente haya terminado la conexion de forma abrupta." << std::endl;
            } else {
                std::cout << e.what() << std::endl;
            }
        }
        this->socket.close();
        this->receiver.stopHandler();
        this->sender.stopHandler();
        this->isClosed = true;
    }
}

