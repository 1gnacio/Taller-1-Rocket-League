#ifndef MATCH_RESPONSE_H
#define MATCH_RESPONSE_H

#include <vector>
#include "../serializer/entity_serializer.h"
#include "../serializer/serializer.h"

class MatchResponse {
private:
    Serializer serializer;
    EntitySerializer entitySerializer;
    int goalsLocal;
    int goalsVisitor;
    int time_insec;
    BallResponse ballResponse;
    PlayerResponses players;
    int requiredPlayers;
    int currentPlayers;
    std::string name;
    bool isWaitingForPlayers;
    bool hasFinished;
    bool isGoalLocal;
    bool isGoalVisitor;
    bool activeReplay;
public:

    MatchResponse(int goalsLocal,
                  int goalsVisitor,
                  int time_insec,
                  BallResponse &ball,
                  PlayerResponses &players,
                  int requiredPlayers,
                  int currentPlayers,
                  std::string &name,
                  bool isWaitingForPlayers,
                  bool hasFinished,
                  bool isGoalLocal,
                  bool isGoalVisitor,
                  bool activeReplay);

    explicit MatchResponse(std::vector<unsigned char>& serialized);
    std::vector<unsigned char> serialize();

    void setGoals(uint8_t goalsLocal, uint8_t goalsVisitor);
    void setPlayers(uint8_t requiredPlayers, uint8_t currentPlayers);
    void setStates(bool isWaitingForPlayers, bool hasFinished, bool isGoalLocal, bool isGoalVisitor, bool activeReplay);
    void setName(std::string &gameName);
    char getSizeGameName();

    static int size(int playerCount, int roomNameSize);
    int size();
};


#endif // MATCH_RESPONSE_H
