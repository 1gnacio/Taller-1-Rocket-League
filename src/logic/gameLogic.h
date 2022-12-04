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
    GameLogic(int requiredPlayers);
    void updateModel(Command &command);
    void addPlayer(int id);
    void updateTime();
    Response getResponse();
    float getCarData(int carNumber, int key);
    float playersAmount();

    void resetData();

    float ballPosY();

    void removePlayer(int i);

    bool isGoal();

    bool matchFinished();

    void updateRoomInfo(Room &room, bool b);

    void resetPositions();
};

#endif  // SRC_LOGIC_GAMELOGIC_H_
