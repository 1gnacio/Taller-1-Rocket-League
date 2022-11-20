#ifndef BOX_LOGIC_MONITOR_H
#define BOX_LOGIC_MONITOR_H

#include <mutex>
#include "../src/protocolo/responses/match_response.h"
#include "boxLogic.h"

class BoxLogicMonitor {
private:
    std::mutex mutex;
    BoxLogic gamePhysics;
public:
    void updateTime();
    BallResponse getBallResponse();
    PlayerResponses getPlayerResponses();
    float getCarData(int carNumber, int key);
    int playersAmount();
    bool hasPlayer(int id);
    void addPlayer(int id);
    void removePlayer(int id);
    void applyLogic(Command &command);
};


#endif // BOX_LOGIC_MONITOR_H
