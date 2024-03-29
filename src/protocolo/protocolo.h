#ifndef COMMON_SRC_PROTOCOLO_H_
#define COMMON_SRC_PROTOCOLO_H_

#include <string>
#include <map>
#include <vector>
#include "../sockets/socket.h"
#include "responses/response.h"
#include "commands/command.h"
#include "protocol_commands.h"

class Protocolo {
 private:
    bool connectionClosed = false;
    int16_t responseBytes = 2;

    void sendAll(Socket &socket, std::vector<unsigned char> &message);
    void receiveAll(Socket &socket, std::vector<unsigned char> &message, uint16_t responseSize);

    void receiveResponseSize(Socket &socket, uint16_t &size);
    void sendResponseSize(Socket &socket, uint16_t size);

    void sendMessage(Socket& socket, std::vector<unsigned char> &message);
    std::vector<unsigned char> receiveMessage(Socket& socket);

 public:
    Protocolo();

    void sendCommand(Socket& socket, Command& command);

    Response receiveResponse(Socket& socket);

    bool isConnectionClosed();

    // una instancia por hilo, recibe los comandos de un cliente
    Command receiveCommand(Socket& socket);

    // una instancia por hilo, envia la respuesta del servidor a un cliente
    void sendResponse(Socket& socket, Response& response);

    void sendId(Socket &socket, int id);

    int receiveId(Socket &socket);
};
#endif  // COMMON_SRC_PROTOCOLO_H_
