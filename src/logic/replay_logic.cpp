#include "replay_logic.h"
#include <utility>

void ReplayLogic::goalScored() {
    this->isActive = true;
    this->elapsedTimeInSec = 0;
    std::size_t replayResponsesAmount = this->replayTimeInSec * this->responsesPerSec;
    if (replayResponsesAmount < this->responses.size()) {
        std::vector replayResponses(this->responses.end() - replayResponsesAmount, this->responses.end());
        this->responses = std::move(replayResponses);
    }
}

void ReplayLogic::addResponse(Response &response) {
    response.setActiveReplay();
    this->responses.push_back(response);
}

ReplayLogic::ReplayLogic(int replayTimeInSec, int responsesPerSec) :
isActive(false),
responses(),
replayTimeInSec(replayTimeInSec),
responsesPerSec(responsesPerSec),
elapsedTimeInSec(0) {}

Response ReplayLogic::getResponse() {
    if (this->responses.empty()) {
        this->isActive = false;
        this->elapsedTimeInSec = this->replayTimeInSec;
        return {true};
    }
    Response response = this->responses.front();
    this->responses.erase(this->responses.begin());
    this->elapsedTimeInSec += 1 / this->responsesPerSec;
    this->isActive = this->elapsedTimeInSec < this->replayTimeInSec;
    return response;
}
