#include <iostream>
#include "game.h"
#include "../protocolo/responses/match_response.h"
#include "../protocolo/responses/ball_response.h"
#include "../protocolo/responses/player_responses.h"
#include "../src/game_entities/room.h"
#include "../src/constants/logic_values.h"

Game::Game(int requiredPlayers, int time, int updateT):
              name("juego"),
              time_inSec(0),
              time_in_miliSec(0),
              goalsLocal(0),
              goalsVisitor(0),
              requiredPlayers(requiredPlayers),
              currentPlayers(1),
              isWaitingForPlayers(requiredPlayers > 1),
              hasFinished(false),
              isGoalLocal(false),
              isGoalVisitor(false),
              activeReplay(false),
              game_time(time),
              update(updateT) {
}

MatchResponse Game::response(BallResponse &ball, PlayerResponses &players) {
    return MatchResponse(goalsLocal, goalsVisitor, time_inSec, ball, players,
                         requiredPlayers, currentPlayers, name,
                         isWaitingForPlayers, hasFinished, isGoalLocal,
                         isGoalVisitor, activeReplay);
}

int Game::getTime() {
    return time_inSec;
}

void Game::updateGame(int teamGoal) {
    if (teamGoal == LogicValues().GOAL_LOCAL) {
        isGoalLocal = 1;
        goalsLocal++;
    } else if (teamGoal == LogicValues().GOAL_VISITOR) {
        isGoalVisitor = 1;
        goalsVisitor++;
    }
}
void Game::updateTime() {
    time_in_miliSec = time_in_miliSec + (1000/update);
    if (time_in_miliSec > 1000) {
        time_inSec++;
        time_in_miliSec = time_in_miliSec - 1000;
    }
}

bool Game::matchFinished() {
    if (time_inSec > game_time)
        hasFinished = true;
    else
        hasFinished = false;

    return hasFinished;
}

bool Game::goal() {
    return (isGoalLocal || isGoalVisitor);
}

void Game::resetData() {
    isGoalVisitor = 0;
    isGoalLocal = 0;
}

void Game::setStatus(Room &room, bool replay) {
    isWaitingForPlayers = !(room.isStarted1());
    activeReplay = replay;
}
