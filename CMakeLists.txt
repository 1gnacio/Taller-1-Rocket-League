cmake_minimum_required(VERSION 3.5)

project(rocket-league VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions(-DDATA_PATH="${PROJECT_SOURCE_DIR}/data")
# start SDL

# set up SDL2pp library
set(SDL2PP_WITH_IMAGE YES)
set(SDL2PP_WITH_TTF YES)
add_subdirectory(SDL2pp)
add_subdirectory(box2d)

# end SDL

# start QT5
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)

# end QT5

#
add_executable(boxExample testBox.cpp)
target_link_libraries(boxExample box2d)
#
add_executable(exampleMerged exampleMerged.cpp)
target_link_libraries(exampleMerged box2d SDL2pp)

add_executable(game exampleGame.cpp)
target_link_libraries(game box2d SDL2pp)

add_executable(game2 exampleGame2.cpp)
target_link_libraries(game2 box2d SDL2pp)

add_executable(lobby
        main_lobby.cpp
        src/lobby/lobby.cpp
        src/lobby/lobby.h
        src/lobby/lobby.ui
        src/sockets/socket.cpp
        src/sockets/socket.h
        src/sockets/liberror.cpp
        src/sockets/liberror.h
        src/sockets/resolver.cpp
        src/sockets/resolvererror.cpp
        src/sockets/resolvererror.h
        src/sockets/resolver.h
        src/sockets/socket.cpp
        src/sockets/socket.h
        src/protocolo/protocolo-tp2.h
        src/protocolo/protocolo-tp2.cpp
        )

 target_link_libraries(lobby Qt5::Widgets)
