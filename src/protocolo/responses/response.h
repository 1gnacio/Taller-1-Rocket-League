//
// Created by ignacio on 30/10/22.
//

#ifndef TALLER_1_ROCKET_LEAGUE_RESPONSE_H
#define TALLER_1_ROCKET_LEAGUE_RESPONSE_H

#include <string>
#include <vector>
#include "ball_response.h"
#include "player_response.h"
#include "lobby_response.h"

class Response {
private:
    // otras posibles respuestas: partida, lobby ...
    BallResponse ballResponse;
    std::vector<PlayerResponse> playerResponse;
    LobbyResponse lobbyResponse;
    std::string responseStatus;
    std::string responseMessage;
public:
    Response(std::vector<char> serializedResponse);
    Response(const char* responseStatus, const char* responseMessage);

    std::vector<char> serialize();
    // aca pueden haber metodos especificos para obtener atributos de cada respuesta
    // o toda la respuesta de ser necesario
};


#endif //TALLER_1_ROCKET_LEAGUE_RESPONSE_H
