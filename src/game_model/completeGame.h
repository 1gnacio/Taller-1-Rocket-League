//
// Created by taller on 25/11/22.
//

#ifndef SRC_GAME_MODEL_COMPLETEGAME_H_
#define SRC_GAME_MODEL_COMPLETEGAME_H_
#include "../game_entities/room.h"
#include "../logic/gameLogic.h"
#include "../handlers/server_endpoint.h"
#include "../logic/replay_logic.h"
#include <string>

class CompleteGame {
 private:
    ServerEndpoint & serverEndpoint;
    ServerConfigurationAttributes configuration;
    Room room;
    GameLogic logic;
    ReplayLogic replayLogic;
    CommandQueue commandQueue;
    bool isClosed;

 public:
    CompleteGame(int ownerId, int requiredPlayers, const char *name, ServerEndpoint&serverEndPoint);
    ActionResultResponse joinPlayer(int id);
    RoomResponse list();
    ActionResultResponse leaveRoom(int playerId);
    Response getResponse();
    bool isInGame();

    bool operator<(const Room &room) const;
    bool operator()(Room& room);
    bool playerInRoom(int id);
    [[nodiscard]] std::string getName() const { return room.getName(); }

    void applyCommand(Command &command);

    void updateTime();
    void resetData();

    void sendResponse();

    void gameFlow();

    bool isInReplay();

    void finally();

    bool matchFinished();

    bool hasPlayers();
};
#endif  // SRC_GAME_MODEL_COMPLETEGAME_H_
