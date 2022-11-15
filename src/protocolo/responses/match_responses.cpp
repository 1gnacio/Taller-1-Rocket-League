#include "match_responses.h"

MatchResponses::MatchResponses(std::vector<MatchResponse> &responses) : matches(responses) {}

// {
// {cantidad de partidas}
// {
//   {
//      {size partida 1} { datos partida 1 }
//   }
//   {
//      {size partida 2} { datos partida 2 }
//   }
//   ...
// }

MatchResponses::MatchResponses(std::vector<unsigned char> &serializedMatchResponses) {
    std::vector<unsigned char> serializedMatchCount(serializedMatchResponses.begin(), serializedMatchResponses.begin() + 4);
    int count = this->serializer.deserializeInt(serializedMatchCount);
    if (count == 0) {
        return;
    }

    std::vector<unsigned char> serializedMatches(serializedMatchResponses.begin() + 4, serializedMatchResponses.end());

    int accumulatedSizes = 0;

    for(int i = 0; i < count; i++) {
        std::vector<unsigned char> serializedMatchSize(serializedMatches.begin() + accumulatedSizes, serializedMatches.begin() + 4 + accumulatedSizes);
        int size = this->serializer.deserializeInt(serializedMatchSize);
        accumulatedSizes += size;

        if (size == 0) {
            continue;
        }

        std::vector<unsigned char> serializedMatch(serializedMatches.begin() + accumulatedSizes + 4, serializedMatches.begin() + size);
        this->matches.emplace_back(serializedMatch);
    }
}

std::vector<unsigned char> MatchResponses::serialize() {
    std::vector<unsigned char> serialization;

    int count = this->matches.size();

    this->serializer.merge(serialization, this->serializer.serializeInt(count));
    this->serializer.merge(serialization, this->serializer.serializeInt(this->size()));

    if(count == 0) {
        return serialization;
    }

    for(auto& response : this->matches) {
        std::vector<unsigned char> serialized = response.serialize();
        this->serializer.merge(serialization, serialized);
    }

    return serialization;
}

MatchResponses::MatchResponses() : matches() {}

int MatchResponses::size() {
    if (this->matches.empty()) {
        return 0;
    }

    int size = 0;

    for (auto& match : this->matches) {
        size += match.size();
    }

    return size;
}

void MatchResponses::addResponse(MatchResponse& response) {
    this->matches.push_back(response);
}
