#include <iostream>
#include <string>
#include <algorithm>
#include <sys/socket.h>
#include "server.h"
#include "../sockets/liberror.h"
#include "../exceptions/socket_closed_exception.h"


// hilos:
// uno que se queda esperando la 'q' de entrada estandar (hilo principal)
// uno que acepte clientes nuevos
// uno por cliente que reciba comandos y haga push a la cola de comandos recibidos
// uno por cliente que haga push a cada cola de respuestas enviadas de cada cliente
//
// colas:
// hay 1 cola de comandos compartida por cada hilo que recibe comandos
// hay 1 cola de respuestas por cada hilo que recibe respuestas
Server::Server(const char* servname) : monitor(), accepter(servname), logic() {}

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
    this->endpoint.stopConnections();
}

void Server::cleanFinishedHandlers() {
    this->endpoint.cleanFinishedConnections();
}

void Server::startHandler(Socket &socket) {
    this->endpoint.addPlayer(socket);
}

void Server::gameFlow(){
    try {
        while(!this->isClosed) {
            logic.resetData();
            Response lastResponse;
            int limitCommands = 0;
            while(!endpoint.queueEmpty() && limitCommands <= 50){
                Command command = endpoint.pop();
                lastResponse = logic.getResponse();
                LobbyResponse lobby = monitor.applyLogic(command);
                lastResponse.addLobbyResponse(lobby);
                logic.updateModel(command);
                limitCommands++;
                endpoint.push(lastResponse);
            }
            logic.updateTime();
            //std::cout << "Actualizo el tiempo en box2d" << std::endl;
            endpoint.push(logic.getResponse());
        }
    } catch (...) {
        throw;
    }
}

void Server::run() {
    while (!this->isClosed) {
        std::thread accepterThread(&Server::acceptClients, this);
        std::thread gameLoopThread(&Server::gameFlow, this);

        std::string signal;

        while (!this->isClosed && std::getline(std::cin, signal)) {
            if (signal == "q") {
                this->isClosed = true;
                this->accepter.shutdown(SHUT_RDWR);
                this->accepter.close();
            }
        }

        accepterThread.join();
        gameLoopThread.join();
    }
}

Server::~Server() {
    this->stopHandlers();
    this->cleanFinishedHandlers();
}

