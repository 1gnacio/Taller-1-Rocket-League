#include <sys/socket.h>
#include <utility>
#include "client_handler.h"
#include "../protocolo/protocolo.h"
#include "../exceptions/socket_closed_exception.h"

ClientHandler::ClientHandler(Socket& socket, GameModelMonitor& monitor) :
    hasFinished(false),
    client(std::move(socket)),
    monitor(monitor),
    thread(&ClientHandler::handle, this) {}

void ClientHandler::stopHandler() {
    this->hasFinished = true;
    this->client.shutdown(SHUT_RDWR);
    this->client.close();
}

bool ClientHandler::finished() {
    return this->hasFinished;
}

void ClientHandler::handle() {
    Protocolo protocolo;

    try{
        while (!this->hasFinished && !protocolo.isConnectionClosed()) {
            Command command = protocolo.receiveCommand();

            Response response = this->monitor.applyLogic(command);

            protocolo.sendResponse(response);
        }
    } catch (SocketClosedException& e) {
        // si se cierra la conexion con el cliente marco el hilo como terminado
    } catch(...) {
        throw;
    }

    this->hasFinished = true;
}

ClientHandler::~ClientHandler() {
    this->thread.join();
}
