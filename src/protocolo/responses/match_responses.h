#ifndef MATCH_RESPONSES_H
#define MATCH_RESPONSES_H

#include <vector>
#include "match_response.h"

class MatchResponses {
private:
    std::vector<MatchResponse> matches;
public:
    std::vector<char> serialize();
};


#endif // MATCH_RESPONSES_H
