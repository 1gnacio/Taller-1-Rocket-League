#ifndef COMMAND_H
#define COMMAND_H

#include <string>

class Command {
private:
    char serialized;
    std::string deserialized;
    std::string firstParameter;
    std::string secondParameter;
public:
    // movimientos, acciones, listar
    Command(char serialized,
            const std::string& deserialized);

    // unirse
    Command(char serialized,
            const std::string& deserialized,
            const std::string& firstParameter);

    // crear
    Command(char serialized,
            const std::string& deserialized,
            const std::string& firstParameter,
            const std::string& secondParameter);

    [[nodiscard]] char serialize() const;
    [[nodiscard]] std::string getValue() const { return this->deserialized; }
    [[nodiscard]] std::string getFirstParameter() const { return this->firstParameter; }
    [[nodiscard]] std::string getSecondParameter() const { return this->secondParameter; }

    // hago los comandos movibles
    Command(Command&&) noexcept ;
    Command& operator=(Command&&) noexcept ;
};


#endif // COMMAND_H
