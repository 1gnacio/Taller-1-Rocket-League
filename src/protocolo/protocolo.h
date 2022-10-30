#ifndef COMMON_SRC_PROTOCOLO_H_
#define COMMON_SRC_PROTOCOLO_H_

#include <string>
#include <map>
#include <vector>
#include "../sockets/socket.h"
#include "command.h"
#include "protocol_commands.h"

class Protocolo {
 private:
    ProtocolCommands protocolCommands;
    bool connectionClosed = false;
    int16_t responseBytes = 2;
    int16_t sentCommandsBytes = 1;

    bool isEndOfCommands(char serializedCommand);

 public:
    Protocolo();

    void sendCommands(Socket& socket,
                      std::vector<Command> commands);

    std::vector<std::string> receiveCommands(Socket& socket);

    void sendMovementResponse(Socket& socket,
                              std::vector<std::string> movement);

    std::string receiveMovementResponse(Socket& socket);

    bool isConnectionClosed();
};
#endif  // COMMON_SRC_PROTOCOLO_H_
