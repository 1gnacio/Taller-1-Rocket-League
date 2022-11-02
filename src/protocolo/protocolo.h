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

    // el servidor recibe comandos de todos los clientes a la vez, no tiene sentido pasarle un socket
    Command receiveCommand();

    // el servidor envia la respuesta a todos los clientes a la vez, no tiene sentido pasarle un socket
    void sendResponse(Response& response);

};
#endif  // COMMON_SRC_PROTOCOLO_H_
