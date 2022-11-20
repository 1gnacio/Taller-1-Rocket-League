#include <sstream>
#include <utility>
#include "response.h"
#include "match_responses.h"

Response::Response(std::vector<unsigned char> &serializedResponse) : serializer() {
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

    this->matchResponses = MatchResponses(serializedMatchesResponse);
}

Response::Response(MatchResponses &matchResponses) : serializer(), matchResponses(std::move(matchResponses)) {}

std::vector<unsigned char> Response::serialize() {
    std::vector<unsigned char> serialization;

    this->serializer.merge(serialization, this->lobbyResponse.serialize());
    this->serializer.merge(serialization, this->matchResponses.serialize());

    return serialization;
}

Response::Response() : lobbyResponse(), matchResponses() {}

MatchResponses Response::getMatchResponses() {
    return matchResponses;
}

void Response::addLobbyResponse(LobbyResponse &response) {
    this->lobbyResponse = response;
}

float Response::getBallPositionY() {
    return this->matchResponses.getMatchResponse().getBall().getPosY();
}

Response::Response(LobbyResponse &lobby) : matchResponses(), lobbyResponse(lobby) {}

Response::Response(LobbyResponse &lobby, MatchResponses &matchResponses)
: lobbyResponse(lobby), matchResponses(matchResponses) {}

std::vector<RoomResponse> Response::getRoomResponses() {
    return this->lobbyResponse.roomResponses();
}
