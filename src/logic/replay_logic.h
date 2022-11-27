#ifndef REPLAY_LOGIC_H
#define REPLAY_LOGIC_H

#include <queue>
#include "../protocolo/responses/match_response.h"
#include "../protocolo/responses/response.h"

class ReplayLogic {
private:
    bool isActive;
    std::vector<Response> responses;
    int replayTimeInSec;
    int responsesPerSec;
    int elapsedTimeInSec;
public:
    ReplayLogic(int replayTimeInSec, int responsesPerSec);
    void goalScored();
    void addResponse(Response &response);
    Response getResponse();
    bool isInReplay() { return this->isActive && this->elapsedTimeInSec < this->replayTimeInSec; };
};


#endif //ROCKET_LEAGUE_REPLAY_LOGIC_H
