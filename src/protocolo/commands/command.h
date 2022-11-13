#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <vector>

class Command {
private:
    char serialized{};
    std::string deserialized;
    std::string firstParameter;
    std::string secondParameter;

public:
    // movimientos, acciones, listar
    Command(unsigned char serialized,
            const std::string& deserialized);

    // unirse
    Command(unsigned char serialized,
            const std::string& deserialized,
            const std::string& firstParameter);

    // crear
    Command(unsigned char serialized,
            const std::string& deserialized,
            const std::string& firstParameter,
            const std::string& secondParameter);

    Command(std::vector<unsigned char> serialized);

    [[nodiscard]] std::vector<unsigned char> serialize();
    [[nodiscard]] std::string getValue() const { return this->deserialized; }
    [[nodiscard]] std::string getFirstParameter() const { return this->firstParameter; }
    [[nodiscard]] std::string getSecondParameter() const { return this->secondParameter; }

    // hago los comandos movibles
    Command(Command&&) noexcept ;
    Command& operator=(Command&&) noexcept ;
};


#endif // COMMAND_H
