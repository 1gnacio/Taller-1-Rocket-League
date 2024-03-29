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

    return result;

}

void MatchResponse::setGoals(uint8_t local, uint8_t visitor) {
    this->goalsLocal = local;
    this->goalsVisitor = visitor;
}

void MatchResponse::setPlayers(uint8_t required, uint8_t current) {
    this->requiredPlayers = required;
    this->currentPlayers = current;
}

void MatchResponse::setStates(bool waitingForPlayers, bool finished, bool goalLocal, bool goalVisitor,
                              bool replay) {
    this->isWaitingForPlayers = waitingForPlayers;
    this->hasFinished = finished;
    this->isGoalLocal = goalLocal;
    this->isGoalVisitor = goalVisitor;
    this->activeReplay = replay;
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
    if (countPlayers != 0) {
        std::vector<unsigned char> playerResponses(serialized.begin() +
                                                   firstPosition,
                                                   serialized.begin() +
                                                   lastPosition +
                                                   PlayerResponses::getSize(countPlayers));

        this->players = PlayerResponses(playerResponses);

        firstPosition += PlayerResponses::getSize(countPlayers);
        lastPosition += PlayerResponses::getSize(countPlayers);
    }
    else{
        this->players = PlayerResponses();
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

PlayerResponses MatchResponse::getPlayersResponse() {
    return players;
}

BallResponse MatchResponse::getBall() {
    return ballResponse;
}

int MatchResponse::getLocalGoals() {
    return goalsLocal;
}

int MatchResponse::getVisitorsGoals() {
    return goalsVisitor;
}

int MatchResponse::getTime() {
    return time_insec;
}

bool MatchResponse::hasPlayer(int i) {
    return this->players.hasPlayer(i);

}

bool MatchResponse::isReplaying() {
    return activeReplay;
}

bool MatchResponse::waitingForPlayers() {
    return isWaitingForPlayers;
}

MatchResponse::MatchResponse() = default;
