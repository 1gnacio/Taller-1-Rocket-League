#include "action_result_response.h"
#include "../serializer/serializer.h"

ActionResultResponse::ActionResultResponse(int id, const std::string &status, const std::string &message)
: id(id), status(status), message(message) {}

ActionResultResponse::ActionResultResponse(int id, const std::string &status)
: id(id), status(status), message() {}

ActionResultResponse::ActionResultResponse(std::vector<unsigned char> &serialized) {
    Serializer serializer;
    int begin = 0;
    int end = 0;

    serializer.parse(this->id, serialized, begin, end);
    serializer.parse(this->status, serialized, begin, end);
    serializer.parse(this->message, serialized, begin, end);
}

std::vector<unsigned char> ActionResultResponse::serialize() {
    Serializer serializer;
    std::vector<unsigned char> serialized;
    std::vector<unsigned char> result;

    serializer.merge(serialized, serializer.serializeInt(this->id));
    serializer.merge(serialized, serializer.serializeString(this->status));
    serializer.merge(serialized, serializer.serializeString(this->message));

    serializer.merge(result, serializer.serializeInt(serialized.size()));
    serializer.merge(result, serialized);

    return result;
}

ActionResultResponse::ActionResultResponse() : id(), status(), message() {}

ActionResultResponse::ActionResultResponse(const std::string &status, const std::string &message)
: status(status), message(message) {}

int ActionResultResponse::getId() {
    return this->id;
}
