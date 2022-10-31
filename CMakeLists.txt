cmake_minimum_required(VERSION 3.5)

project(Lobby VERSION 0.1 LANGUAGES CXX)

# set up SDL2pp library
set(SDL2PP_WITH_IMAGE YES)
set(SDL2PP_WITH_TTF YES)
add_subdirectory(SDL2pp)
add_subdirectory(box2d)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
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

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Lobby
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Lobby APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Lobby SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Lobby
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Lobby PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(Lobby PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS Lobby
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Lobby)
endif()

# define targets 
add_executable(SDLExample testSDL.cc)
target_link_libraries(SDLExample PUBLIC SDL2pp)
#target_link_libraries(testing PUBLIC src)

add_executable(boxExample testBox.cpp)
target_link_libraries(boxExample box2d)

add_executable(exampleMerged exampleMerged.cpp)
target_link_libraries(exampleMerged box2d SDL2pp)

add_executable(game exampleGame.cpp)
target_link_libraries(game box2d SDL2pp)

# define targets
add_executable(testing testing.cc)
target_link_libraries(testing PUBLIC SDL2pp)
