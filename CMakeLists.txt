cmake_minimum_required(VERSION 3.5)

project(rocket-league VERSION 0.1 LANGUAGES CXX)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Flags TODO: activarlo
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3 -pedantic -pedantic-errors")
# debugging flags
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -DDEBUG -fno-inline ")

add_definitions(-DDATA_PATH="${PROJECT_SOURCE_DIR}/data")

#start YAML
find_package(yaml-cpp REQUIRED)
#end YAML
#####################################################################################################################
# start SDL
# set up SDL2pp library
#find_package(SDL2pp REQUIRED)
set(SDL2PP_WITH_IMAGE ON) # if you need SDL_image support
set(SDL2PP_WITH_MIXER ON) # if you need SDL_mixer support
set(SDL2PP_WITH_TTF ON) # if you need SDL_ttf support
add_subdirectory(libs/libSDL2pp)
add_subdirectory(box2d)
include_directories(${PROJECT_SOURCE_DIR}/libs)
include_directories(${SDL2PP_INCLUDE_DIRS})
# end SDL
######################################################################################################################
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
######################################################################################################################
add_executable(boxExample testBox.cpp)
target_link_libraries(boxExample box2d)

######################################################################################################################
add_executable(exampleMerged exampleMerged.cpp)
target_link_libraries(exampleMerged box2d ${SDL2PP_LIBRARIES})

######################################################################################################################
add_executable(game exampleGame.cpp)
target_link_libraries(game box2d ${SDL2PP_LIBRARIES})

######################################################################################################################
######################################################################################################################
add_executable(gameSensors sensors.cpp)
target_link_libraries(gameSensors box2d ${SDL2PP_LIBRARIES})
######################################################################################################################

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
        src/handlers/server_connection.cpp
        src/handlers/server_connection.cpp
        src/client/client.cpp
        src/client/client.h
        src/client_sdl/sdl_main.cpp
        src/client_sdl/sdl_main.h
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
        src/protocolo/protocolo.h
        src/protocolo/protocolo.cpp
        src/queues/response_queue.cpp
        src/queues/response_queue.h
        src/protocolo/responses/response.cpp
        src/protocolo/responses/response.h
        src/protocolo/serializer/entity_serializer.cpp
        src/protocolo/serializer/entity_serializer.h
        src/protocolo/serializer/serializer.cpp
        src/protocolo/serializer/serializer.h
        src/handlers/server_endpoint.cpp
        src/handlers/server_endpoint.h
        src/handlers/client_connection.cpp
        src/handlers/client_connection.h
        src/game_model/completeGame.cpp
        src/game_model/game_model.cpp
        src/game_model/completeGame.h
        src/game_model/game_model.h
        src/game_entities/room.cpp
        src/game_entities/room.h
        src/logic/gameLogic.cpp
        src/logic/gameLogic.h
        src/logic/boxLogic.cpp
        src/logic/boxLogic.h
        src/logic/car.cpp
        src/logic/car.h
        src/logic/SoccerGoal.cpp
        src/logic/SoccerGoal.h
        src/logic/game.cpp
        src/logic/game.h
        src/logic/contactListenerHits.cpp
        src/logic/contactListenerHits.h
        src/protocolo/serializer/serializer.cpp
        src/protocolo/serializer/serializer.h
        src/protocolo/responses/match_response.cpp
        src/protocolo/responses/match_response.h
        src/protocolo/responses/match_responses.cpp
        src/protocolo/responses/match_responses.h
        src/protocolo/responses/player_response.h
        src/protocolo/responses/player_response.cpp
        src/protocolo/responses/player_responses.cpp
        src/protocolo/responses/player_responses.h
        src/protocolo/responses/ball_response.cpp
        src/protocolo/responses/ball_response.h
        src/protocolo/serializer/entity_serializer.cpp
        src/protocolo/serializer/entity_serializer.h
        src/queues/block_queues/command_blocking_queue.cpp
        src/queues/block_queues/command_blocking_queue.h
        src/queues/block_queues/response_blocking_queue.cpp
        src/queues/block_queues/response_blocking_queue.h
        src/lobby/lobby.cpp
        src/lobby/lobby.h
        src/lobby/lobby.ui
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
        src/protocolo/protocolo.h
        src/protocolo/protocolo.cpp
        src/queues/response_queue.cpp
        src/queues/response_queue.h
        src/sockets/resolvererror.cpp
        src/sockets/resolvererror.h
        src/protocolo/responses/response.cpp
        src/protocolo/responses/response.h
        src/protocolo/serializer/entity_serializer.cpp
        src/protocolo/serializer/entity_serializer.h
        src/client/client.cpp src/client/client.h
        src/handlers/server_connection.cpp src/handlers/server_connection.h
        src/protocolo/protocol_commands.cpp src/protocolo/protocol_commands.h
        src/sockets/socket.cpp src/sockets/socket.h
        src/queues/command_queue.cpp src/queues/command_queue.h
        src/handlers/command_handler.cpp src/handlers/command_handler.h
        src/handlers/response_handler.cpp src/handlers/response_handler.h
        src/protocolo/commands/strategies/create_parameter_strategy.cpp src/protocolo/commands/strategies/create_parameter_strategy.h
        src/protocolo/commands/command.cpp src/protocolo/commands/command.h
        src/sockets/resolver.cpp src/sockets/resolver.h
        src/sockets/liberror.cpp src/sockets/liberror.h
        src/protocolo/protocolo.h src/protocolo/protocolo.cpp
        src/queues/response_queue.cpp src/queues/response_queue.h
        src/sockets/resolvererror.cpp src/sockets/resolvererror.h
        src/protocolo/responses/response.cpp src/protocolo/responses/response.h
        src/client_sdl/sdl_main.cpp src/client_sdl/sdl_main.h
        src/client_sdl/sdl_player.h src/client_sdl/sdl_player.cpp
        src/client_sdl/sdl_animation.cpp src/client_sdl/sdl_animation.h
        src/client_sdl/sdl_ball.cpp src/client_sdl/sdl_ball.h
        src/client_sdl/sdl_arena.cpp src/client_sdl/sdl_arena.h
        src/client_sdl/sdl_scoreboard.cpp src/client_sdl/sdl_scoreboard.h
        src/protocolo/serializer/serializer.cpp
        src/protocolo/serializer/serializer.h
        src/client_sdl/sdl_animation.cpp
        src/client_sdl/sdl_animation.h
        src/client_sdl/sdl_waiting.h
        src/client_sdl/sdl_waiting.cpp
        src/client_sdl/sdl_statistics.h
        src/client_sdl/sdl_statistics.cpp
        src/client_sdl/sdl_player.cpp
        src/client_sdl/sdl_main.h src/client_sdl/sdl_ball.cpp src/client_sdl/sdl_ball.h src/client_sdl/sdl_scoreboard.cpp src/client_sdl/sdl_scoreboard.h src/client_sdl/sdl_arena.cpp src/client_sdl/sdl_arena.h
        src/common/unit_conversion.cpp src/common/unit_conversion.h
        src/protocolo/responses/lobby_response.cpp
        src/protocolo/responses/lobby_response.h
        src/protocolo/responses/room_responses.cpp
        src/protocolo/responses/room_responses.h
        src/protocolo/responses/room_response.cpp
        src/protocolo/responses/room_response.h
        src/protocolo/responses/connected_clients.cpp
        src/protocolo/responses/connected_clients.h
        src/protocolo/responses/action_result_response.cpp
        src/protocolo/responses/action_result_response.h
        src/logic/replay_logic.cpp
        src/logic/replay_logic.h
        src/handlers/id_service.cpp
        src/handlers/id_service.h
        src/logic/ball.cpp
        src/logic/ball.h
        src/configuration/attributes/client_configuration_attributes.cpp
        src/configuration/attributes/client_configuration_attributes.h
        src/configuration/attributes/server_configuration_attributes.cpp
        src/configuration/attributes/server_configuration_attributes.h
        src/configuration/yaml_configuration.cpp
        src/configuration/yaml_configuration.h
        src/client_sdl/sdl_waiting.h
        src/client_sdl/sdl_waiting.cpp
        )

target_link_libraries(lobby ${SDL2PP_LIBRARIES} Qt5::Widgets box2d yaml-cpp)

######################################################################################################################
file(GLOB_RECURSE sources "../src/*/*.cpp")
file(GLOB_RECURSE headers "../src/*/*.h")

add_executable(game_client
        client_main.cpp
        src/thread/common_thread.cpp
        src/thread/common_thread.h
        src/lobby/lobby.cpp
        src/lobby/lobby.h
        src/lobby/lobby.ui
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
        src/protocolo/serializer/entity_serializer.cpp
        src/protocolo/serializer/entity_serializer.h
        src/client/client.cpp src/client/client.h
        src/handlers/server_connection.cpp src/handlers/server_connection.h
        src/protocolo/protocol_commands.cpp src/protocolo/protocol_commands.h
        src/sockets/socket.cpp src/sockets/socket.h
        src/queues/command_queue.cpp src/queues/command_queue.h
        src/handlers/command_handler.cpp src/handlers/command_handler.h
        src/handlers/response_handler.cpp src/handlers/response_handler.h
        src/protocolo/commands/strategies/create_parameter_strategy.cpp src/protocolo/commands/strategies/create_parameter_strategy.h
        src/protocolo/commands/command.cpp src/protocolo/commands/command.h
        src/sockets/resolver.cpp src/sockets/resolver.h
        src/sockets/liberror.cpp src/sockets/liberror.h
        src/protocolo/protocolo.h src/protocolo/protocolo.cpp
        src/queues/response_queue.cpp src/queues/response_queue.h
        src/sockets/resolvererror.cpp src/sockets/resolvererror.h
        src/protocolo/responses/response.cpp src/protocolo/responses/response.h
        src/client_sdl/sdl_main.cpp src/client_sdl/sdl_main.h
        src/client_sdl/sdl_player.h src/client_sdl/sdl_player.cpp
        src/client_sdl/sdl_animation.cpp src/client_sdl/sdl_animation.h
        src/client_sdl/sdl_ball.cpp src/client_sdl/sdl_ball.h
        src/client_sdl/sdl_arena.cpp src/client_sdl/sdl_arena.h
        src/client_sdl/sdl_scoreboard.cpp src/client_sdl/sdl_scoreboard.h
        src/client_sdl/sdl_waiting.h
        src/client_sdl/sdl_waiting.cpp
        src/protocolo/serializer/serializer.cpp
        src/protocolo/serializer/serializer.h
        src/protocolo/responses/match_response.cpp
        src/protocolo/responses/match_response.h
        src/protocolo/responses/match_responses.cpp
        src/protocolo/responses/match_responses.h
        src/protocolo/responses/ball_response.cpp
        src/protocolo/responses/ball_response.h
        src/protocolo/responses/player_responses.cpp
        src/protocolo/responses/player_responses.h
        src/protocolo/responses/player_response.cpp
        src/protocolo/responses/player_response.h
        src/client_sdl/sdl_animation.cpp
        src/client_sdl/sdl_animation.h
        src/client_sdl/sdl_player.cpp
        src/client_sdl/sdl_main.cpp
        src/client_sdl/sdl_main.h src/client_sdl/sdl_ball.cpp src/client_sdl/sdl_ball.h src/client_sdl/sdl_scoreboard.cpp src/client_sdl/sdl_scoreboard.h src/client_sdl/sdl_arena.cpp src/client_sdl/sdl_arena.h
        src/protocolo/responses/player_response.h
        src/protocolo/responses/player_response.cpp
        src/protocolo/responses/player_responses.cpp
        src/protocolo/responses/player_responses.h
        src/protocolo/responses/ball_response.cpp
        src/protocolo/responses/ball_response.h
        src/queues/block_queues/command_blocking_queue.cpp
        src/queues/block_queues/command_blocking_queue.h
        src/queues/block_queues/response_blocking_queue.cpp
        src/queues/block_queues/response_blocking_queue.h
        src/common/unit_conversion.cpp src/common/unit_conversion.h
        src/protocolo/responses/lobby_response.cpp
        src/protocolo/responses/lobby_response.h
        src/protocolo/responses/room_responses.cpp
        src/protocolo/responses/room_responses.h
        src/protocolo/responses/room_response.cpp
        src/protocolo/responses/room_response.h
        src/protocolo/responses/connected_clients.cpp
        src/protocolo/responses/connected_clients.h
        src/protocolo/responses/action_result_response.cpp
        src/protocolo/responses/action_result_response.h
        src/configuration/attributes/client_configuration_attributes.cpp
        src/configuration/attributes/client_configuration_attributes.h
        src/configuration/attributes/server_configuration_attributes.cpp
        src/configuration/attributes/server_configuration_attributes.h
        src/configuration/yaml_configuration.cpp
        src/configuration/yaml_configuration.h
        src/constants/configuration_paths.h
        src/thread/common_thread.cpp
        src/thread/common_thread.h
        src/handlers/id_service.cpp
        src/handlers/id_service.h
        src/client_sdl/sdl_waiting.h
        src/client_sdl/sdl_waiting.cpp
        src/client_sdl/sdl_statistics.cpp src/client_sdl/sdl_statistics.h src/client_sdl/sdl_music.cpp src/client_sdl/sdl_music.h)
        

target_link_libraries(game_client ${SDL2PP_LIBRARIES} Qt5::Widgets yaml-cpp)

######################################################################################################################

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
        src/protocolo/serializer/entity_serializer.cpp
        src/protocolo/serializer/entity_serializer.h
        src/protocolo/serializer/serializer.cpp
        src/protocolo/serializer/serializer.h
        src/protocolo/responses/match_response.cpp
        src/protocolo/responses/match_response.h
        src/protocolo/responses/match_responses.cpp
        src/protocolo/responses/match_responses.h
        src/protocolo/responses/ball_response.cpp
        src/protocolo/responses/ball_response.h
        src/protocolo/responses/player_responses.cpp
        src/protocolo/responses/player_responses.h
        src/protocolo/responses/player_response.cpp
        src/protocolo/responses/player_response.h
        src/game_model/completeGame.cpp
        src/game_model/completeGame.h
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
        src/logic/car.cpp
        src/logic/car.h
        src/logic/SoccerGoal.cpp
        src/logic/SoccerGoal.h
        src/logic/game.cpp
        src/logic/game.h
        src/protocolo/serializer/serializer.cpp
        src/protocolo/serializer/serializer.h
        src/protocolo/responses/match_response.cpp
        src/protocolo/responses/match_response.h
        src/protocolo/responses/match_responses.cpp
        src/protocolo/responses/match_responses.h
        src/protocolo/responses/player_response.h
        src/protocolo/responses/player_response.cpp
        src/protocolo/responses/player_responses.cpp
        src/protocolo/responses/player_responses.h
        src/protocolo/responses/ball_response.cpp
        src/protocolo/responses/ball_response.h
        src/protocolo/serializer/entity_serializer.cpp
        src/protocolo/serializer/entity_serializer.h
        src/queues/block_queues/command_blocking_queue.cpp
        src/queues/block_queues/command_blocking_queue.h
        src/queues/block_queues/response_blocking_queue.cpp
        src/queues/block_queues/response_blocking_queue.h
        src/protocolo/responses/lobby_response.cpp
        src/protocolo/responses/lobby_response.h
        src/protocolo/responses/room_responses.cpp
        src/protocolo/responses/room_responses.h
        src/protocolo/responses/room_response.cpp
        src/protocolo/responses/room_response.h
        src/protocolo/responses/connected_clients.cpp
        src/protocolo/responses/connected_clients.h
        src/protocolo/responses/action_result_response.cpp
        src/protocolo/responses/action_result_response.h
        src/thread/common_thread.cpp
        src/thread/common_thread.h
        src/handlers/id_service.cpp
        src/handlers/id_service.h
        src/logic/replay_logic.cpp
        src/logic/replay_logic.h
        src/logic/contactListenerHits.cpp
        src/logic/contactListenerHits.h
        src/logic/ball.cpp
        src/logic/ball.h
        src/configuration/attributes/client_configuration_attributes.cpp
        src/configuration/attributes/client_configuration_attributes.h
        src/configuration/attributes/server_configuration_attributes.cpp
        src/configuration/attributes/server_configuration_attributes.h
        src/configuration/yaml_configuration.cpp
        src/configuration/yaml_configuration.h
        )

target_link_libraries(game_server box2d yaml-cpp)

######################################################################################################################
enable_testing()

add_subdirectory(google_tests)
include(CTest)
######################################################################################################################

#**************************************
#***************Install****************
#**************************************

set(BIN "/usr/bin")
set(RESOURCES "/var/game")
set(CONFIG "/etc/game")


install(TARGETS game_client DESTINATION ${BIN} PERMISSIONS WORLD_READ WORLD_WRITE WORLD_EXECUTE)

install(TARGETS game_server DESTINATION ${BIN} PERMISSIONS WORLD_READ WORLD_WRITE WORLD_EXECUTE)

install(TARGETS lobby DESTINATION ${BIN} PERMISSIONS WORLD_READ WORLD_WRITE WORLD_EXECUTE)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/data DESTINATION ${RESOURCES})

install(DIRECTORY ${CMAKE_SOURCE_DIR}/data/config DESTINATION ${CONFIG})



