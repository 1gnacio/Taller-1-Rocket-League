#include "match_response.h"


MatchResponse::MatchResponse(){

}

std::vector<char> MatchResponse::serialize() {

    std::vector<char> response;

    //Goles
    response.push_back((char)goalsLocal);
    response.push_back((char)goalsVisitor);

    // Jugadores
    response.push_back((char)requiredPlayers);
    response.push_back((char)currentPlayers);

    // Estados
    response.push_back((char)isWaitingForPlayers);
    response.push_back((char)hasFinished);
    response.push_back((char)isGoalLocal);
    response.push_back((char)isGoalVisitor);
    response.push_back((char)activeReplay);

    // Nombre de partida
    response.push_back(getSizeGameName());
    for(auto x: name){
        response.push_back(x);
    }


    return std::move(response);

}

void MatchResponse::setGoals(uint8_t goalsLocal, uint8_t goalsVisitor) {
    this->goalsLocal = goalsLocal;
    this->goalsVisitor = goalsVisitor;
}

void MatchResponse::setPlayers(uint8_t requiredPlayers, uint8_t currentPlayers) {
    this->requiredPlayers = requiredPlayers;
    this->currentPlayers = currentPlayers;
}

void MatchResponse::setStates(bool isWaitingForPlayers, bool hasFinished, bool isGoalLocal, bool isGoalVisitor,
                              bool activeReplay) {
    this->isWaitingForPlayers = isWaitingForPlayers;
    this->hasFinished = hasFinished;
    this->isGoalLocal = isGoalLocal;
    this->isGoalVisitor = isGoalVisitor;
    this->activeReplay = activeReplay;
}

void MatchResponse::setName(std::string &gameName) {
    this->name = gameName;
}

char MatchResponse::getSizeGameName() {

    uint8_t i = name.size();
    char*p = (char*)&i;

    return p[0];
}
