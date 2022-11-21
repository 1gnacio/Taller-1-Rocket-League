#include <algorithm>
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

MatchResponses::MatchResponses(std::vector<unsigned char> &serializedMatchResponses) : serializer() {
    int begin = 0;
    int end = 0;
    int count = 0;

    this->serializer.parse(count, serializedMatchResponses, begin, end);

    for(int i = 0; i < count; i++) {
        int size = 0;
        this->serializer.parse(size, serializedMatchResponses, begin, end);
        std::vector<unsigned char> match(serializedMatchResponses.begin() + end + 1,
                                         serializedMatchResponses.begin() + end + size + 1);
        this->matches.emplace_back(match);
        begin += size;
        end += size;
    }
}

std::vector<unsigned char> MatchResponses::serialize() {
    std::vector<unsigned char> serialization;
    std::vector<unsigned char> result;

    int count = this->matches.size();

    this->serializer.merge(serialization, this->serializer.serializeInt(count));

    for(auto& response : this->matches) {
        std::vector<unsigned char> serialized = response.serialize();
        this->serializer.merge(serialization, serialized);
    }

    this->serializer.merge(result, this->serializer.serializeInt(serialization.size()));
    this->serializer.merge(result, serialization);

    return result;
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

MatchResponse MatchResponses::getMatchResponse(int id) {
    auto found = std::find_if(this->matches.begin(),
                              this->matches.end(),
                              [&id] (MatchResponse &match)
                              { return match.hasClient(id);});

    if (found == this->matches.end()) {
        return MatchResponse(true);
    }

    return *found;
}

int MatchResponses::totalPlayers() {
    int count = 0;
    for (auto &matches : this->matches) {
        count += matches.getPlayersResponse().getCount();
    }

    return count;
}
