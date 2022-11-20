#ifndef SRC_LOGIC_GAMELOGIC_H_
#define SRC_LOGIC_GAMELOGIC_H_

#include <thread>
#include <atomic>
#include "../protocolo/commands/command.h"
#include "../protocolo/responses/response.h"
#include "game.h"
#include "../src/queues/block_queues/command_blocking_queue.h"
#include "box_logic_monitor.h"

class GameLogic {
 private:
    bool isStarted;
    int commandCount;
    BoxLogicMonitor gamePhysics;
    Game game;
    CommandBlockingQueue commandQueue;
    std::thread updateModelHandler;

private:
    void updateModel();

public:
    explicit GameLogic(int ownerId, const char* name);
    bool withoutPlayers;
    MatchResponse getResponse();
    float getCarData(int carNumber, int key);
    float playersAmount();
    bool hasPlayer(int id);
    std::string getName() { return this->game.getName(); };
    void addPlayer(int id) { this->gamePhysics.addPlayer(id); };
    void removePlayer(int id) { this->gamePhysics.removePlayer(id); };
    void push(Command &command) { this->commandQueue.push(command); };

    ~GameLogic();
};

#endif  // SRC_LOGIC_GAMELOGIC_H_
