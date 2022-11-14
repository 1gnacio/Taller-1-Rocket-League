#include <strstream>
#include <utility>
#include "response.h"

Response::Response(std::vector<unsigned char> &serializedResponse) : serializer() {
    std::vector<unsigned char> serializedCount(serializedResponse.begin(), serializedResponse.begin() + 3);
    int count = this->serializer.deserializeInt(serializedCount);

    if (count == 0) {
        return;
    }

    std::vector<unsigned char> serializedResponses(serializedResponse.begin() + 4, serializedResponse.end());

    this->matchResponses = std::move(MatchResponses(serializedResponses));
}

Response::Response(MatchResponses &matchResponses) : serializer(), matchResponses(std::move(matchResponses)) {}

std::vector<unsigned char> Response::serialize() {
    std::vector<unsigned char> serialization;
    int count = this->matchResponses.count();

    this->serializer.merge(serialization, this->serializer.serializeInt(count));

    if (count == 0) {
        return serialization;
    }

    this->serializer.merge(serialization, this->matchResponses.serialize());

    return serialization;
}

Response::Response() : lobbyResponse(), matchResponses(), responseStatus() {}

Response::Response(const char *responseStatus, const char *responseMessage) : responseStatus(responseStatus) {}
