#include "response.h"

Response::Response(std::vector<char> serializedResponse) {
    // a partir de la respuesta serializada armar los atributos del objeto,
    // posible resolucion agregar strategies por cada atributo
    // (ballresponsestrategy, playerresponsestrategy, ...)
}

Response::Response(const char* responseStatus, const char* responseMessage)
: responseStatus(responseStatus), responseMessage(responseMessage) {}

std::vector<char> Response::serialize() {
    // TODO serialize response
    return std::vector<char>();
}