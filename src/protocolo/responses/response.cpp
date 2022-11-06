#include <strstream>
#include "response.h"
#include "../../constants/serialize_delimeter.h"
#include "../../constants/response_values.h"

Response::Response(std::vector<char> serializedResponse) {
    std::string currentLine;
    std::vector<std::string> responseParts;
    std::istrstream stream(reinterpret_cast<const char*>(serializedResponse.data()), serializedResponse.size());
    SerializerDelimeter delimeter;

    while (std::getline(stream, currentLine, delimeter.LOBBYDELIMETER)) {
        responseParts.push_back(currentLine);
    }

    if (responseParts.empty()) {
        this->responseStatus = ResponseValues().ERROR;
    } else {
        this->responseStatus = responseParts[0];
        // continuar deserializacion
    }
}

Response::Response(const char* responseStatus, const char* responseMessage)
: responseStatus(responseStatus) {}

std::vector<char> Response::serialize() {
    std::vector<char> result;
    SerializerDelimeter delimeter;

    result.insert(result.end(), this->responseStatus.begin(), this->responseStatus.end());

    result.insert(result.end(), delimeter.LOBBYDELIMETER);

    std::vector<char> serializedLobby = this->lobbyResponse.serialize();

    result.insert(result.end(), serializedLobby.begin(), serializedLobby.end());

    result.insert(result.end(), delimeter.LOBBYDELIMETER);

    std::vector<char> serializedMatches = this->matchResponses.serialize();

    result.insert(result.end(), serializedMatches.begin(), serializedMatches.end());

    return {result.begin(), result.end()};
}