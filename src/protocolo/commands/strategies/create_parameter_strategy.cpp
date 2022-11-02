#include "create_parameter_strategy.h"

std::string CreateParameterStrategy::firstParameter(std::string& parameters) {
    // el primer parametro son la cantidad de jugadores requeridos
    // TODO primeros dos caracteres? definimos una cantidad maxima de jugadores requeridos?
    return parameters.substr(0, 2);
}

std::string CreateParameterStrategy::secondParameter(std::string& parameters) {
    // el segundp parametro es el nombre de la sala
    return parameters.substr(2);
}