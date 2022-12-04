#include <iostream>
#include <SDL2pp/SDL2pp.hh>
#include "src/client/client.h"
#include <QApplication>
#include "src/lobby/lobby.h"
#include "src/configuration/yaml_configuration.h"

int main(int argc, char* argv[]) try {
    if (argc != 3) {
        return -1;
    }

    try {
        ClientConfigurationAttributes configuration =
                YamlConfiguration().ReadClientConfiguration();
    } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
        return -1;
    }

    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(DATA_PATH "/icon.ico"));
    lobby window(nullptr, argv[1], argv[2]);
    window.show();
    return  app.exec();

    } catch (SDL2pp::Exception& e){
        std::cerr << "Error in: " << e.GetSDLFunction() << std::endl;
        std::cerr << "  Reason: " << e.GetSDLError() << std::endl;
        return -1;
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

