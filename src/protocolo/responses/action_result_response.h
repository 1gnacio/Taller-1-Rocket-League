#ifndef ACTION_RESULT_RESPONSE_H
#define ACTION_RESULT_RESPONSE_H

#include <string>
#include <vector>

class ActionResultResponse {
private:
    int id;
    std::string status;
    std::string message;
public:
    ActionResultResponse();
    ActionResultResponse(const std::string &status, const std::string &message);
    ActionResultResponse(int id, const std::string &status, const std::string &message);
    ActionResultResponse(int id, const std::string &status);
    explicit ActionResultResponse(std::vector<unsigned char> &serialized);
    std::vector<unsigned char> serialize();
    std::string getStatus() { return this->status; };
    std::string getMessage() { return this->message; };
};


#endif // ACTION_RESULT_RESPONSE_H
