#include "match_responses.h"

MatchResponses::MatchResponses(std::vector<MatchResponse> &responses) : matches(responses) {}

// {
// {cantidad de partidas}
// {
//   {
//      {size partida 1} { {cantidad de jugadores} {largo nombre} datos partida 1 }
//   }
//   {
//      {size partida 2} { {cantidad de jugadores} {largo nombre} datos partida 2 }
//   }
//   ...
// }

MatchResponses::MatchResponses(std::vector<unsigned char> &serializedMatchResponses) {
    std::vector<unsigned char> serializedMatchCount(serializedMatchResponses.begin(), serializedMatchResponses.begin() + 3);
    int count = this->serializer.deserializeInt(serializedMatchCount);
    if (count == 0) {
        return;
    }

    std::vector<unsigned char> serializedMatches(serializedMatchResponses.begin() + 4, serializedMatchResponses.end());

    for(int i = 0; i < count; i++) {
        std::vector<unsigned char> serializedMatchSize(serializedMatches.begin(), serializedMatches.begin() + 3);
        int size = this->serializer.deserializeInt(serializedMatchSize);

        std::vector<unsigned char> serializedMatch(serializedMatches.begin() + 4, serializedMatches.begin() + size);
        this->matches.emplace_back(serializedMatch);
    }
}

std::vector<unsigned char> MatchResponses::serialize() {
    std::vector<unsigned char> serialization;

    int count = this->matches.size();

    this->serializer.merge(serialization, this->serializer.serializeInt(count));

    if(count == 0) {
        return serialization;
    }

    for(auto& response : this->matches) {
        this->serializer.merge(serialization, response.serialize());
    }

    return serialization;
}

MatchResponses::MatchResponses() : matches() {}
