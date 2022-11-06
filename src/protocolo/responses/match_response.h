#ifndef MATCH_RESPONSE_H
#define MATCH_RESPONSE_H

#include <vector>
#include "player_response.h"
#include "ball_response.h"

class MatchResponse {
private:
    int goalsLocal;
    int goalsVisitor;
    int time; // MMSS, ejemplo: 05:00 se envia como 500
    BallResponse ballResponse;
    std::vector<PlayerResponse> players;
    int requiredPlayers;
    int currentPlayers;
    std::string name;
    bool isWaitingForPlayers;
    bool hasFinished;
    bool isGoalLocal;
    bool isGoalVisitor;
    bool activeReplay;
public:
    std::vector<char> serialize();
};


#endif // MATCH_RESPONSE_H
