cmake_minimum_required(VERSION 3.5)

project(rocket-league VERSION 0.1 LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions(-DDATA_PATH="${PROJECT_SOURCE_DIR}/data")
# start SDL

# set up SDL2pp library
set(SDL2PP_WITH_IMAGE YES)
set(SDL2PP_WITH_TTF YES)
add_subdirectory(libs/libSDL2pp)
add_subdirectory(box2d)
include_directories(${PROJECT_SOURCE_DIR}/libs)
include_directories(${SDL2PP_INCLUDE_DIRS})

# end SDL

# start QT5
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()


set(CMAKE_PREFIX_PATH $ENV{HOME}/Documents/Qt/5.15.2/gcc_64)
find_package(Qt5 COMPONENTS Widgets REQUIRED)


# end QT5

add_executable(boxExample testBox.cpp)
target_link_libraries(boxExample box2d)
#
add_executable(exampleMerged exampleMerged.cpp)
target_link_libraries(exampleMerged box2d ${SDL2PP_LIBRARIES})

add_executable(game exampleGame.cpp)
target_link_libraries(game box2d ${SDL2PP_LIBRARIES})

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

file(GLOB_RECURSE sources "../src/*/*.cpp")
file(GLOB_RECURSE headers "../src/*/*.h")

add_executable(game_client
        client_main.cpp
        src/client/client.cpp
        src/client/client.h
        src/handlers/server_connection.cpp
        src/handlers/server_connection.h
        src/protocolo/protocol_commands.cpp
        src/protocolo/protocol_commands.h
        src/sockets/socket.cpp
        src/sockets/socket.h
        src/queues/command_queue.cpp
        src/queues/command_queue.h
        src/handlers/command_handler.cpp
        src/handlers/command_handler.h
        src/handlers/response_handler.cpp
        src/handlers/response_handler.h
        src/protocolo/commands/strategies/create_parameter_strategy.cpp
        src/protocolo/commands/strategies/create_parameter_strategy.h
        src/protocolo/commands/command.cpp
        src/protocolo/commands/command.h
        src/sockets/resolver.cpp
        src/sockets/resolver.h
        src/sockets/liberror.cpp
        src/sockets/liberror.h
        src/protocolo/protocolo.h
        src/protocolo/protocolo.cpp
        src/queues/response_queue.cpp
        src/queues/response_queue.h
        src/sockets/resolvererror.cpp
        src/sockets/resolvererror.h
        src/protocolo/responses/response.cpp
        src/protocolo/responses/response.h
        src/client/sdl_animation.cpp
        src/client/sdl_animation.h
        src/client/sdl_player.cpp
        src/client/sdl_main.cpp
        src/client/sdl_main.h src/client/sdl_ball.cpp src/client/sdl_ball.h src/client/sdl_scoreboard.cpp src/client/sdl_scoreboard.h src/client/sdl_arena.cpp src/client/sdl_arena.h)

target_link_libraries(game_client box2d ${SDL2PP_LIBRARIES})

add_executable(game_server
        server_main.cpp
        src/server/server.cpp
        src/server/server.h
        src/handlers/server_connection.cpp
        src/handlers/server_connection.h
        src/protocolo/protocol_commands.cpp
        src/protocolo/protocol_commands.h
        src/sockets/socket.cpp
        src/sockets/socket.h
        src/queues/command_queue.cpp
        src/queues/command_queue.h
        src/handlers/command_handler.cpp
        src/handlers/command_handler.h
        src/handlers/response_handler.cpp
        src/handlers/response_handler.h
        src/protocolo/commands/strategies/create_parameter_strategy.cpp
        src/protocolo/commands/strategies/create_parameter_strategy.h
        src/protocolo/commands/command.cpp
        src/protocolo/commands/command.h
        src/sockets/resolver.cpp
        src/sockets/resolver.h
        src/sockets/liberror.cpp
        src/sockets/liberror.h
        src/protocolo/protocolo.h
        src/protocolo/protocolo.cpp
        src/queues/response_queue.cpp
        src/queues/response_queue.h
        src/sockets/resolvererror.cpp
        src/sockets/resolvererror.h
        src/protocolo/responses/response.cpp
        src/protocolo/responses/response.h
        src/game_model/game_model_monitor.cpp
        src/game_model/game_model_monitor.h
        src/handlers/server_endpoint.cpp
        src/handlers/server_endpoint.h
        src/handlers/client_connection.cpp
        src/handlers/client_connection.h
        src/game_model/game_model.cpp
        src/game_model/game_model.h
        src/game_entities/room.cpp
        src/game_entities/room.h
        src/logic/gameLogic.cpp
        src/logic/gameLogic.h
        src/logic/boxLogic.cpp
        src/logic/boxLogic.h
        )

target_link_libraries(game_server box2d)

add_subdirectory(google_tests)
