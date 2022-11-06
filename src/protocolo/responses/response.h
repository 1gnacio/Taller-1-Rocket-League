//
// Created by ignacio on 30/10/22.
//

#ifndef TALLER_1_ROCKET_LEAGUE_RESPONSE_H
#define TALLER_1_ROCKET_LEAGUE_RESPONSE_H

#include <string>
#include <vector>
#include "lobby_response.h"
#include "match_responses.h"

class Response {
private:
    LobbyResponse lobbyResponse;
    MatchResponses matchResponses;
    std::string responseStatus;
public:
    Response(std::vector<char> serializedResponse);
    Response(const char* responseStatus, const char* responseMessage);

    std::string getStatus() { return this->responseStatus; }
    std::vector<char> serialize();
    // aca pueden haber metodos especificos para obtener atributos de cada respuesta
    // o toda la respuesta de ser necesario
};


#endif //TALLER_1_ROCKET_LEAGUE_RESPONSE_H
