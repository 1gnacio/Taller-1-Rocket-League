#ifndef COMMON_SRC_PROTOCOLO_H_
#define COMMON_SRC_PROTOCOLO_H_

#include <string>
#include <map>
#include <vector>
#include "../sockets/socket.h"

class Protocolo {
 private:
    bool connectionClosed = false;
    int16_t responseBytes = 2;
    int16_t sentCommandsBytes = 1;

    char SERIALIZED_NOP = 0x00;
    char SERIALIZED_JUMP_PUSHED = 0x20;
    char SERIALIZED_JUMP_RELEASE = 0x21;
    char SERIALIZED_TURBO_PUSHED = 0x22;
    char SERIALIZED_TURBO_RELEASE = 0x23;
    char SERIALIZED_RIGHT_PUSHED = 0x10;
    char SERIALIZED_RIGHT_RELEASE = 0x11;
    char SERIALIZED_LEFT_PUSHED = 0x12;
    char SERIALIZED_LEFT_RELEASE = 0x13;
    char SERIALIZED_UP_PUSHED = 0x14;
    char SERIALIZED_UP_RELEASE = 0x15;
    char SERIALIZED_DOWN_PUSHED = 5x16;
    char SERIALIZED_DOWN_RELEASE = 5x17;

    std::string DESERIALIZED_JUMP = "JUMP";
    std::string DESERIALIZED_RIGHT = "RIGHT";
    std::string DESERIALIZED_LEFT = "LEFT";
    std::string DESERIALIZED_UP = "UP";
    std::string DESERIALIZED_DOWN = "DOWN";
    std::string DESERIALIZED_TURBO = "TURBO";

    bool isEndOfCommands(char serializedCommand);

 public:
    Protocolo();

    void sendCommands(Socket& socket,
                      std::vector<std::string> commands);

    std::vector<std::string> receiveCommands(Socket& socket);

    void sendMovementResponse(Socket& socket,
                              std::vector<std::string> movement);

    std::string receiveMovementResponse(Socket& socket);

    bool isConnectionClosed();
};
#endif  // COMMON_SRC_PROTOCOLO_H_
