#include <iostream>
#include "src/server/server.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        return -1;
    }

    try {
        Server server(argv[1]);

        server.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
