#include "src/lobby/lobby.h"
#include <iostream>
#include <exception>
#include <QApplication>

int main(int argc, char *argv[]) try {
    QApplication a(argc, argv);
    lobby w;
    w.show();
    return a.exec();
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
