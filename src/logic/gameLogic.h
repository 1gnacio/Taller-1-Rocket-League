#ifndef SRC_LOGIC_GAMELOGIC_H_
#define SRC_LOGIC_GAMELOGIC_H_

#include "boxLogic.h"
#include "../protocolo/commands/command.h"
#include "../protocolo/responses/response.h"
#include "game.h"
#include "../src/game_entities/room.h"

class GameLogic {
 private:
    BoxLogic gamePhysics;

 public:
    explicit GameLogic(int requiredPlayers);
    void updateModel(const Command &command);
    void addPlayer(int id);
    void updateTime();
    Response getResponse();

    void resetData();

    void removePlayer(int i);

    bool isGoal();

    bool matchFinished();

    void updateRoomInfo(Room &room, bool b);
};

#endif  // SRC_LOGIC_GAMELOGIC_H_
