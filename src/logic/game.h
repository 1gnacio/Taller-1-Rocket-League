#ifndef SRC_LOGIC_GAME_H_
#define SRC_LOGIC_GAME_H_

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

    void updateGame(int i);

    bool goal();

    void resetData();
};

#endif  // SRC_LOGIC_GAME_H_
