#ifndef ROCKET_LEAGUE_GAME_H
#define ROCKET_LEAGUE_GAME_H

#include <string>
#include "../protocolo/responses/match_response.h"
#include "../protocolo/responses/ball_response.h"
#include "../protocolo/responses/player_responses.h"


class Game {
private:

    std::string name;
    int time_inSec;
    int goalsLocal;
    int goalsVisitor;
    int requiredPlayers;
    int currentPlayers;
    bool isWaitingForPlayers;
    bool hasFinished;
    bool isGoalLocal;
    bool isGoalVisitor;
    bool activeReplay;
public:
    Game();
    MatchResponse response(BallResponse &ball, PlayerResponses &players);

};




#endif //ROCKET_LEAGUE_GAME_H
