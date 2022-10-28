cmake_minimum_required(VERSION 2.4)
project(testingBox2D)


#incluyo cmake de la biblioteca
#add_subdirectory(SDL2pp)
add_subdirectory(box2d)

INCLUDE_DIRECTORIES()
INCLUDE_DIRECTORIES()
#file(GLOB_RECURSE BOX2D_SRCS ./box2d/src/*.cpp)
#add_library(libbox2d STATIC ${BOX2D_SRCS})


#incluyo ejectuable
add_executable(test test.cpp)
target_link_libraries(test box2d)
