#ifndef MATCH_RESPONSE_H
#define MATCH_RESPONSE_H

#include <vector>
#include "player_response.h"
#include "ball_response.h"

class MatchResponse {
private:
    uint8_t goalsLocal;
    uint8_t goalsVisitor;
    int time; // MMSS, ejemplo: 05:00 se envia como 500
    BallResponse ballResponse;
    std::vector<PlayerResponse> players;
    uint8_t requiredPlayers;
    uint8_t currentPlayers;
    std::string name;
    bool isWaitingForPlayers;
    bool hasFinished;
    bool isGoalLocal;
    bool isGoalVisitor;
    bool activeReplay;
public:

    MatchResponse();
    std::vector<char> serialize();

    void setGoals(uint8_t goalsLocal, uint8_t goalsVisitor);
    void setPlayers(uint8_t requiredPlayers, uint8_t currentPlayers);
    void setStates(bool isWaitingForPlayers, bool hasFinished, bool isGoalLocal, bool isGoalVisitor, bool activeReplay);
    void setName(std::string &gameName);
    char getSizeGameName();
};


#endif // MATCH_RESPONSE_H
