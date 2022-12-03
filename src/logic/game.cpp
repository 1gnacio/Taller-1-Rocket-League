#include <iostream>
#include "game.h"
#include "../protocolo/responses/match_response.h"
#include "../protocolo/responses/ball_response.h"
#include "../protocolo/responses/player_responses.h"
#include "../src/game_entities/room.h"

Game::Game(): name("juego"),
              time_inSec(0),
              time_in_miliSec(0),
              goalsLocal(0),
              goalsVisitor(0),
              requiredPlayers(2),
              currentPlayers(2),
              isWaitingForPlayers(true),
              hasFinished(false),
              isGoalLocal(false),
              isGoalVisitor(false),
              activeReplay(false) {
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
    if(teamGoal == 2) {
        isGoalLocal = 1;
        goalsLocal++;
    } else if(teamGoal == 1) {
        isGoalVisitor = 1;
        goalsVisitor++;
    }

}
void Game::updateTime() {
    time_in_miliSec = time_in_miliSec + 40;
    if(time_in_miliSec > 1000) {
        time_inSec++;
        time_in_miliSec = time_in_miliSec - 1000;
    }
}

bool Game::matchFinished() {
    return (time_inSec > 180);
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
    hasFinished = room.isFinished1();
    activeReplay = replay;

}
