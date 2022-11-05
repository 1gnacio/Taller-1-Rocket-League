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
    ProtocolCommands protocolCommands;
    bool connectionClosed = false;
    int16_t responseBytes = 2;
    int16_t sentCommandsBytes = 1;

    bool isEndOfCommands(char serializedCommand);
    std::vector<char> serializeMovementCommands(std::vector<Command> &commands);

 public:
    Protocolo();

    void sendCommand(Socket& socket, Command& command);

    Response receiveResponse(Socket& socket);

    bool isConnectionClosed();

    // una instancia por hilo, recibe los comandos de un cliente
    Command receiveCommand(Socket& socket);

    // una instancia por hilo, envia la respuesta del servidor a un cliente
    void sendResponse(Socket& socket, Response& response);

};
#endif  // COMMON_SRC_PROTOCOLO_H_
