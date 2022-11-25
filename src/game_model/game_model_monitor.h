//
// Created by ignacio on 01/10/22.
//

#ifndef GAME_MODEL_MONITOR_H
#define GAME_MODEL_MONITOR_H

#include <vector>
#include <string>
#include <mutex>
#include "game_model.h"
#include "../protocolo/responses/response.h"
#include "../protocolo/commands/command.h"
#include "../protocolo/protocol_commands.h"

class GameModelMonitor {
 private:
    std::mutex mutex;
    GameModel model;
    CommandValues commands;

    LobbyResponse listRooms(int id);
    LobbyResponse joinRoom(int id, const char* name);
    LobbyResponse createRoom(int id, const char* name, int requiredPlayers);
    LobbyResponse leaveRoom(int id, const char* name);


 public:
    void run();
    GameModelMonitor();
    LobbyResponse applyLogic(Command& command);
    std::vector<Response> getResponse();
    int gamesAmount();

    // hago el monitor del modelo de juego no copiable
    GameModelMonitor(const GameModelMonitor&) = delete;
    GameModelMonitor& operator=(const GameModelMonitor&) = delete;

    void applyCommandToGame(Command &command);

    void updateTime();

    void resetDataOfGames();
};


#endif // GAME_MODEL_MONITOR_H
