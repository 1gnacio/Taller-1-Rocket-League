#include "game.h"
#include "../protocolo/responses/match_response.h"
#include "../protocolo/responses/ball_response.h"
#include "../protocolo/responses/player_responses.h"

Game::Game(): name("juego"),
              time_inSec(0),
              goalsLocal(0),
              goalsVisitor(0),
              requiredPlayers(2),
              currentPlayers(2),
              isWaitingForPlayers(false),
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

void Game::updateGame(int teamGoal) {
    if(teamGoal == 1) {
        isGoalLocal = 1;
        goalsLocal++;
    } else if(teamGoal == 2) {
        isGoalVisitor = 1;
        goalsVisitor++;
    }

}

bool Game::goal() {

    return (isGoalLocal || isGoalVisitor);
}

void Game::resetData() {
    isGoalVisitor = 0;
    isGoalLocal = 0;
}
