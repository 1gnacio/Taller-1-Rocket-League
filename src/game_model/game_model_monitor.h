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
