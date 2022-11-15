#include <sstream>
#include <utility>
#include "response.h"
#include "match_responses.h"

Response::Response(std::vector<unsigned char> &serializedResponse) : serializer() {
    std::vector<unsigned char> serializedCount(serializedResponse.begin(), serializedResponse.begin() + 4);

    int count = this->serializer.deserializeInt(serializedCount);

    if (count == 0) {
        return;
    }

    std::vector<unsigned char> serializedMatchesSize(serializedResponse.begin() + 4, serializedResponse.begin() + 8);

    int size = this->serializer.deserializeInt(serializedMatchesSize);

    std::vector<unsigned char> serializedMatchResponses(serializedResponse.begin() + 8, serializedResponse.begin() + 8 + size);

    int accumulatedSize = 0;

    for (int i = 0; i < count; i++) {
        std::vector<unsigned char> serializedMatchSize(serializedMatchResponses.begin() + accumulatedSize,
                                                       serializedMatchResponses.begin() + accumulatedSize + 4);

        int matchSize = this->serializer.deserializeInt(serializedMatchSize);

        std::vector<unsigned char> match(serializedMatchResponses.begin() + accumulatedSize + 4,
                                         serializedMatchResponses.begin() + 4 + accumulatedSize + matchSize);
        accumulatedSize += matchSize;

        MatchResponse matchResponse(match);

        this->matchResponses.addResponse(matchResponse);
    }
}

Response::Response(MatchResponses &matchResponses) : serializer(), matchResponses(std::move(matchResponses)) {}

std::vector<unsigned char> Response::serialize() {
    std::vector<unsigned char> serialization;

    int count = this->matchResponses.count();

    if (count == 0) {
        return serialization;
    }

    this->serializer.merge(serialization, this->matchResponses.serialize());

    return serialization;
}

Response::Response() : lobbyResponse(), matchResponses(), responseStatus() {}

Response::Response(const char *responseStatus, const char *responseMessage) : responseStatus(responseStatus) {}
