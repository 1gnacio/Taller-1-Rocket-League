#ifndef SRC_LOGIC_GAME_H_
#define SRC_LOGIC_GAME_H_

#include <string>
#include "../protocolo/responses/match_response.h"
#include "../protocolo/responses/ball_response.h"
#include "../protocolo/responses/player_responses.h"
#include "../src/game_entities/room.h"

/*
 * Clase que se encarga de manipular los datos de la partida, como por ejemplo el tiempo y los
 * goles de los equipos.
 */
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
    int update;

 public:
    Game(int requiredPlayers, int time, int update);
    MatchResponse response(BallResponse &ball, PlayerResponses &players);

    /*
     * Verifica si hay goles y modifica los estados
     *  key:
     *  1 -> Gol local
     *  2 -> Gol visitante
     *  0 -> No hay goles
     */
    void updateGame(int key);

    bool goal();

    void resetData();

    void updateTime();

    int getTime();

    void setStatus(bool b);

    bool matchFinished();

    void setStatus(Room &room, bool replay);
};

#endif  // SRC_LOGIC_GAME_H_
