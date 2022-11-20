//
// Created by ignacio on 30/10/22.
//

#ifndef TALLER_1_ROCKET_LEAGUE_RESPONSE_H
#define TALLER_1_ROCKET_LEAGUE_RESPONSE_H

#include <string>
#include <vector>
#include "lobby_response.h"
#include "../serializer/serializer.h"
#include "match_responses.h"

class Response {
private:
    Serializer serializer;
    LobbyResponse lobbyResponse;
    MatchResponses matchResponses;
public:
    Response();
    Response(LobbyResponse &lobby, MatchResponses &matchResponses);
    Response(std::vector<unsigned char> &serializedResponse);
    Response(MatchResponses &matchResponses);
    Response(LobbyResponse &lobby);

    std::string getStatus() { return this->lobbyResponse.getStatus(); };
    std::vector<unsigned char> serialize();
    // aca pueden haber metodos especificos para obtener atributos de cada respuesta
    // o toda la respuesta de ser necesario
    int getSize() { return this->matchResponses.size(); };
    MatchResponses getMatchResponses();
    void addLobbyResponse(LobbyResponse &response);
    float getBallPositionY();
    std::vector<RoomResponse> getRoomResponses();

    int getActionId();
};


#endif //TALLER_1_ROCKET_LEAGUE_RESPONSE_H
