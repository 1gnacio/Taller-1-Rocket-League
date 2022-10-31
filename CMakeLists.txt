# SDL2pp tutorial
#
# Written in 2015 by Dmitry Marakasiv <amdmi3@amdmi3.ru>
#
# To the extent possible under law, the author(s) have dedicated all copyright
# and related and neighboring rights to this software to the public domain
# worldwide. This software is distributed without any warranty.
#
# You should have received a copy of the CC0 Public Domain Dedication along with
# this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.

cmake_minimum_required(VERSION 3.16 FATAL_ERROR)
project(SDL2pp-tutorial LANGUAGES CXX)

# set up SDL2pp library
set(SDL2PP_WITH_IMAGE YES)
set(SDL2PP_WITH_TTF YES)
add_subdirectory(SDL2pp)
add_subdirectory(box2d)

# add compilation flags
set(CMAKE_CXX_STANDARD 17)
add_definitions(-DDATA_PATH="${PROJECT_SOURCE_DIR}/data")
include_directories(${SDL2PP_INCLUDE_DIRS})

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
