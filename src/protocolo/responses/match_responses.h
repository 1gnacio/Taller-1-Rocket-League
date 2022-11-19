#ifndef MATCH_RESPONSES_H
#define MATCH_RESPONSES_H

#include <vector>
#include "../serializer/serializer.h"
#include "match_response.h"

class MatchResponses {
private:
    Serializer serializer;
    std::vector<MatchResponse> matches;
public:
    MatchResponses();
    explicit MatchResponses(std::vector<MatchResponse> &responses);
    explicit MatchResponses(std::vector<unsigned char> &serializedMatchResponse);
    std::vector<unsigned char> serialize();

    int count() { return this->matches.size(); };
    int size();

    void addResponse(MatchResponse &response);
    MatchResponse getMatchResponse();
};


#endif // MATCH_RESPONSES_H
