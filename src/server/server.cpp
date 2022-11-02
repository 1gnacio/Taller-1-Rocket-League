#include <iostream>
#include <string>
#include <algorithm>
#include <sys/socket.h>
#include "server.h"
#include "../sockets/liberror.h"
#include "../sockets/socket_closed_exception.h"

Server::Server(const char* servname) : monitor(), accepter(servname) {}

Socket Server::acceptClient() {
    // lanzo una excepcion custom cuando se cierra el socket
    // aceptador por cierre manual del servidor
    try{
        return this->accepter.accept();
    } catch (LibError& e) {
        throw SocketClosedException(e);
    } catch (...) {
        throw;
    }
}

void Server::acceptClients() {
    try {
        while (!this->isClosed) {
            Socket client = this->acceptClient();
            this->startHandler(client);
            this->cleanFinishedHandlers();
        }

        this->stopHandlers();
    } catch (SocketClosedException& e) {
        this->stopHandlers();
        this->cleanFinishedHandlers();
        return;
    } catch (...) {
        throw;
    }
}

void Server::stopHandlers() {
    for (auto & handler : this->clientHandlers) {
        handler->stopHandler();
    }
}

bool waitIfFinished(std::unique_ptr<ClientHandler>& handler) {
    return handler->finished();
}

void Server::cleanFinishedHandlers() {
    this->clientHandlers.erase(std::remove_if(this->clientHandlers.begin(),
                                              this->clientHandlers.end(),
                                              waitIfFinished),
                                              this->clientHandlers.end());
}

void Server::startHandler(Socket &socket) {
    this->clientHandlers.push_back(std::make_unique<ClientHandler>(socket, this->monitor));
}

void Server::run() {
    while (!this->isClosed) {
        std::thread accepterThread(&Server::acceptClients, this);

        std::string signal;

        while (!this->isClosed && std::getline(std::cin, signal)) {
            if (signal == "q") {
                this->isClosed = true;
                this->accepter.shutdown(SHUT_RDWR);
                this->accepter.close();
            }
        }

        accepterThread.join();
    }
}

Server::~Server() {
    this->stopHandlers();
    this->cleanFinishedHandlers();
}

