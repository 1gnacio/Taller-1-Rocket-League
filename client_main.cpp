#include <iostream>
#include "src/client/client.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        return -1;
    }

    try {
        // ej "localhost" "8080"
        Client client(argv[1], argv[2]);

        client.run();
    } catch (std:: exception &e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
