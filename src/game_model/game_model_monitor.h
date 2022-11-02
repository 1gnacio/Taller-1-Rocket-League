//
// Created by ignacio on 01/10/22.
//

#ifndef GAME_MODEL_MONITOR_H
#define GAME_MODEL_MONITOR_H

#include <vector>
#include <string>
#include <mutex>
#include "../common_src/command.h"
#include "../common_src/response.h"
#include "game_model.h"
#include "../common_src/available_commands.h"

class GameModelMonitor {
 private:
    std::mutex mutex;
    GameModel model;
    AvailableCommands commands;

    std::vector<std::string> serializedRooms();
    Response listRooms();
    Response joinRoom(const char* name);
    Response createRoom(const char* name, uint8_t requiredPlayers);
 public:
    GameModelMonitor();
    Response applyLogic(const Command& command);

    // hago el monitor del modelo de juego no copiable
    GameModelMonitor(const GameModelMonitor&) = delete;
    GameModelMonitor& operator=(const GameModelMonitor&) = delete;
};


#endif // GAME_MODEL_MONITOR_H
