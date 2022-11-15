#include <iostream>
#include "src/client/client.h"
#include <QApplication>

int main(int argc, char* argv[]) try {
    if (argc != 3) {
        return -1;
    }

    // ej "localhost" "8080"
    Client client(argv[1], argv[2]);
    //if (client.runLobby());
    client.run();

    return 0;
    } catch (const std::exception& err) {
        std::cerr
                << "Something went wrong and an exception was caught: "
                << err.what()
                << "\n";
        return -1;
    } catch (...) {
        std::cerr
                << "Something went wrong and"
                   " an unknown exception was caught.\n";
        return -1;
    }