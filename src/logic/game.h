#ifndef SRC_LOGIC_GAME_H_
#define SRC_LOGIC_GAME_H_

#include <string>
#include "../protocolo/responses/match_response.h"
#include "../protocolo/responses/ball_response.h"
#include "../protocolo/responses/player_responses.h"
#include "../src/game_entities/room.h"


class Game {
 private:
    std::string name;
    int time_inSec;
    int time_in_miliSec;
    int goalsLocal;
    int goalsVisitor;
    int requiredPlayers;
    int currentPlayers;
    bool isWaitingForPlayers;
    bool hasFinished;
    bool isGoalLocal;
    bool isGoalVisitor;
    bool activeReplay;
    int game_time;
 public:
    Game(int requiredPlayers, int time);
    MatchResponse response(BallResponse &ball, PlayerResponses &players);

    void updateGame(int i);

    bool goal();

    void resetData();

    void updateTime();

    int getTime();

    void setStatus(bool b);

    bool matchFinished();

    void setStatus(Room &room, bool replay);
};

#endif  // SRC_LOGIC_GAME_H_
