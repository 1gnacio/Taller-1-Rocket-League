#include <sstream>
#include <utility>
#include "response.h"
#include "match_responses.h"

Response::Response(std::vector<unsigned char> &serializedResponse) : serializer(), isDummy(false) {
    if (serializedResponse.empty()) {
        return;
    }

    int lobbySize = 0;
    int matchesSize = 0;
    int begin = 0;
    int end = 0;

    this->serializer.parse(lobbySize, serializedResponse, begin, end);

    std::vector<unsigned char> serializedLobbyResponse(serializedResponse.begin() + end + 1,
                                                       serializedResponse.begin() + end + lobbySize + 1);

    this->lobbyResponse = LobbyResponse(serializedLobbyResponse);

    begin += lobbySize;
    end += lobbySize;

    this->serializer.parse(matchesSize, serializedResponse, begin, end);

    std::vector<unsigned char> serializedMatchesResponse(serializedResponse.begin() + end + 1,
                                                         serializedResponse.begin() + end + matchesSize + 1);

    this->matchResponse = MatchResponse(serializedMatchesResponse);
}

Response::Response(MatchResponse &matchResponse)
: serializer(), matchResponse(std::move(matchResponse)), isDummy(false) {}

std::vector<unsigned char> Response::serialize() {
    std::vector<unsigned char> serialization;

    this->serializer.merge(serialization, this->lobbyResponse.serialize());
    this->serializer.merge(serialization, this->matchResponse.serialize());

    return serialization;
}

Response::Response() : lobbyResponse(), matchResponse(), isDummy(false) {}

void Response::addLobbyResponse(LobbyResponse &response) {
    this->lobbyResponse = response;
}

float Response::getBallPositionY() {
    return this->matchResponse.getBall().getPosY();
}

Response::Response(LobbyResponse &lobby) : matchResponse(), lobbyResponse(lobby) {}

bool Response::isRecipient(int id) {

    return this->lobbyResponse.isRecipient(id);
}

MatchResponse Response::getMatchResponse() {
    return this->matchResponse;
}

std::vector<RoomResponse> Response::getRooms() {
    return this->lobbyResponse.getRooms();
}

void Response::setActiveReplay() {
    this->matchResponse.setActiveReplay();
}

Response::Response(bool isDummy) : isDummy(isDummy) {}

int Response::getTime() {
   return this->matchResponse.getTime();
}
