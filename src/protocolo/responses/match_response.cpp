#include <utility>
#include "match_response.h"

std::vector<unsigned char> MatchResponse::serialize() {
    std::vector<unsigned char> result;
    std::vector<unsigned char> serialization;

    this->serializer.merge(serialization, this->serializer.serializeInt(goalsLocal));
    this->serializer.merge(serialization, this->serializer.serializeInt(goalsVisitor));
    this->serializer.merge(serialization, this->serializer.serializeInt(time_insec));
    this->serializer.merge(serialization, this->ballResponse.serialize());
    this->serializer.merge(serialization, this->players.serialize());
    this->serializer.merge(serialization, this->serializer.serializeInt(requiredPlayers));
    this->serializer.merge(serialization, this->serializer.serializeInt(currentPlayers));
    this->serializer.merge(serialization, this->serializer.serializeString(name));
    this->serializer.merge(serialization, this->serializer.serializeBool(isWaitingForPlayers));
    this->serializer.merge(serialization, this->serializer.serializeBool(hasFinished));
    this->serializer.merge(serialization, this->serializer.serializeBool(isGoalLocal));
    this->serializer.merge(serialization, this->serializer.serializeBool(isGoalVisitor));
    this->serializer.merge(serialization, this->serializer.serializeBool(activeReplay));

    int size = serialization.size();

    this->serializer.merge(result, this->serializer.serializeInt(size));
    this->serializer.merge(result, serialization);

    return std::move(result);

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

int MatchResponse::size(int playerCount, int roomNameSize) {
    return sizeof(MatchResponse::goalsLocal)
    + sizeof(MatchResponse::goalsVisitor)
    + sizeof(MatchResponse::time_insec)
    + BallResponse::size()
    + playerCount * PlayerResponse::size()
    + sizeof(MatchResponse::requiredPlayers)
    + sizeof(MatchResponse::currentPlayers)
    + roomNameSize
    + 1 // isWaitingForPlayers
    + 1 // hasFinished
    + 1 // isGoalLocal
    + 1 // isGoalVisitor
    + 1 // activeReplay
    ;
}

int MatchResponse::size() {
    return sizeof(MatchResponse::goalsLocal)
           + sizeof(MatchResponse::goalsVisitor)
           + sizeof(MatchResponse::time_insec)
           + BallResponse::size()
           + this->players.getSize() + sizeof(int)
           + sizeof(MatchResponse::requiredPlayers)
           + sizeof(MatchResponse::currentPlayers)
           + this->name.size() + sizeof(int)
           + 1 // isWaitingForPlayers
           + 1 // hasFinished
           + 1 // isGoalLocal
           + 1 // isGoalVisitor
           + 1 // activeReplay
            ;
}

MatchResponse::MatchResponse(std::vector<unsigned char>& serialized) :
        serializer(), entitySerializer() {
    int firstPosition = 0;
    int lastPosition = 0;

    this->serializer.parse(this->goalsLocal, serialized, firstPosition, lastPosition);
    this->serializer.parse(this->goalsVisitor, serialized, firstPosition, lastPosition);
    this->serializer.parse(this->time_insec, serialized, firstPosition, lastPosition);
    this->entitySerializer.parse(this->ballResponse, serialized, firstPosition, lastPosition);

    int countPlayers = 0;
    this->serializer.parse(countPlayers, serialized, firstPosition, lastPosition);

    for(int i = 0; i < countPlayers; i++) {
        PlayerResponse p;
        this->entitySerializer.parse(p, serialized, firstPosition, lastPosition);
        this->players.addPlayer(p);
    }

    this->serializer.parse(this->requiredPlayers, serialized, firstPosition, lastPosition);
    this->serializer.parse(this->currentPlayers, serialized, firstPosition, lastPosition);
    this->serializer.parse(this->name, serialized, firstPosition, lastPosition);
    this->serializer.parse(this->isWaitingForPlayers, serialized, firstPosition, lastPosition);
    this->serializer.parse(this->hasFinished, serialized, firstPosition, lastPosition);
    this->serializer.parse(this->isGoalLocal, serialized, firstPosition, lastPosition);
    this->serializer.parse(this->isGoalVisitor, serialized, firstPosition, lastPosition);
    this->serializer.parse(this->activeReplay, serialized, firstPosition, lastPosition);
}

MatchResponse::MatchResponse(int goalsLocal, int goalsVisitor, int time_insec, BallResponse &ball,
                             PlayerResponses &players, int requiredPlayers, int currentPlayers,
                             std::string &name, bool isWaitingForPlayers, bool hasFinished, bool isGoalLocal,
                             bool isGoalVisitor, bool activeReplay) :
                             goalsLocal(goalsLocal), goalsVisitor(goalsVisitor), time_insec(time_insec),
                             ballResponse(ball), players(std::move(players)), requiredPlayers(requiredPlayers),
                             currentPlayers(currentPlayers), name(std::move(name)), isWaitingForPlayers(isWaitingForPlayers),
                             hasFinished(hasFinished), isGoalLocal(isGoalLocal), isGoalVisitor(isGoalVisitor),
                             activeReplay(activeReplay) {
}

float MatchResponse::getBallPositionY() {
    return ballResponse.getPosY();
}

