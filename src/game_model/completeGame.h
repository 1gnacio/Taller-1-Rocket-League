//
// Created by taller on 25/11/22.
//

#ifndef ROCKET_LEAGUE_COMPLETEGAME_H
#define ROCKET_LEAGUE_COMPLETEGAME_H
#include "../game_entities/room.h"
#include "../logic/gameLogic.h"
#include "../handlers/server_endpoint.h"
#include "../logic/replay_logic.h"

class CompleteGame {
private:
    Room room;
    GameLogic logic;
    ServerEndpoint & serverEndpoint;
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
    [[nodiscard]] std::string getName() const { return room.getName(); };

    // CompleteGame(const CompleteGame &game, Room room);
    void applyCommand(Command &command);
    float ballPosY();

    void updateTime();
    void resetData();

    void sendResponse();

    void gameFlow();

    bool isInReplay();

    void finally();

    bool matchFinished();

    bool hasPlayers();
};





#endif //ROCKET_LEAGUE_COMPLETEGAME_H
