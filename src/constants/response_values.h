#ifndef RESPONSE_VALUES_H
#define RESPONSE_VALUES_H

#include <string>

class ResponseValues {
public:
    const std::string OK = "OK";
    const std::string ERROR = "ERROR";
    const std::string ROOM_ALREADY_EXISTS = "LA SALA YA EXISTE";
    const std::string PLAYER_ALREADY_JOINED = "YA ESTA UNIDO A LA PARTIDA";
    const std::string ROOM_ALREADY_FULL = "LA PARTIDA ESTA LLENA";
    const std::string ROOM_NOT_FOUND = "NO SE ENCONTRO LA PARTIDA";
    const std::string PLAYER_NOT_FOUND = "JUGADOR NO ENCONTRADO";
    const std::string CONNECTION_CLOSED = "DESCONECTADO";
};

#endif // RESPONSE_VALUES_H
