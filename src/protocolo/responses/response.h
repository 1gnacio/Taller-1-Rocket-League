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
    MatchResponse matchResponse;
    bool isDummy;
public:
    Response();
    Response(bool isDummy);
    Response(std::vector<unsigned char> &serializedResponse);
    Response(MatchResponse &matchResponse);
    Response(LobbyResponse &lobby);

    bool isRecipient(int id);
    std::string getStatus() { return this->lobbyResponse.getStatus(); };
    std::vector<unsigned char> serialize();
    // aca pueden haber metodos especificos para obtener atributos de cada respuesta
    // o toda la respuesta de ser necesario
    void addLobbyResponse(LobbyResponse &response);
    float getBallPositionY();
    std::vector<RoomResponse> getRooms();
    void setActiveReplay();
    bool dummy() {return this->isDummy;};

    MatchResponse getMatchResponse();
};


#endif //TALLER_1_ROCKET_LEAGUE_RESPONSE_H
