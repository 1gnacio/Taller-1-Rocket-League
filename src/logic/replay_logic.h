#ifndef SRC_LOGIC_REPLAY_LOGIC_H_
#define SRC_LOGIC_REPLAY_LOGIC_H_

#include <queue>
#include <vector>
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
    bool isInReplay() { return this->isActive && this->elapsedTimeInSec < this->replayTimeInSec; }
};

#endif  // SRC_LOGIC_REPLAY_LOGIC_H_
