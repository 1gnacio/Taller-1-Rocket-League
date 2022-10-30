#include "protocolo-tp2.h"
#include <sstream>
#include <string>
#include <algorithm>

ClientProtocolo::ClientProtocolo(const char *hostname, const char *port)
: socket(hostname, port) {was_closed=false;}

void ClientProtocolo::sendActions(std::string message) {
    message.append("\n\n");
    int sz= socket.sendall(
            message.c_str(), message.size(), &was_closed);

    if (sz != (int)message.size()) {
        throw std::runtime_error("No se pudo enviar todos los datos\n");
    }

    if (was_closed) {
        throw std::runtime_error("Se cerro el socket\n");
    }
}

std::string ClientProtocolo::receiveResponse() {
    char letter;
    std::string response;
    std::size_t found;
    do {
        int sz = socket.recvall(&letter, sizeof(letter), &was_closed);
        if (was_closed) {
            throw std::runtime_error("Se cerro el socket\n");
        }
        if (sz != sizeof(letter)){
            throw std::runtime_error("No se pudo recibir todos los datos\n");
        }
        response.push_back(letter);
        found = response.find("\n\n");
    } while (found == std::string::npos);
    response.pop_back();
    response.pop_back();
    //Borro el OK
    std::cout << response << std::endl;
    if (response.size() > 2) {
                response=response.substr(3);
    }
    return response;
}

bool ClientProtocolo::isRunning() {
    return !was_closed;
}


