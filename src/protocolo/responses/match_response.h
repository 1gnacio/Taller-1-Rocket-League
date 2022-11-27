#ifndef MATCH_RESPONSE_H
#define MATCH_RESPONSE_H

#include <vector>
#include <string>
#include "../serializer/serializer.h"
#include "ball_response.h"
#include "player_responses.h"

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
    explicit MatchResponse();
    std::vector<unsigned char> serialize();

    void setGoals(uint8_t goalsLocal, uint8_t goalsVisitor);
    void setPlayers(uint8_t requiredPlayers, uint8_t currentPlayers);
    void setStates(bool isWaitingForPlayers, bool hasFinished, bool isGoalLocal, bool isGoalVisitor, bool activeReplay);
    void setName(std::string &gameName);
    char getSizeGameName();

    static int size(int playerCount, int roomNameSize);
    int size();
    int getLocalGoals();
    int getVisitorsGoals();
    int getTime();
    PlayerResponses getPlayersResponse();
    BallResponse getBall();
    void setActiveReplay() { this->activeReplay = true; };

    bool hasPlayer(int i);
};


#endif // MATCH_RESPONSE_H
