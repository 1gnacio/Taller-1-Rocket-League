# 'Google_test' is the subproject name
project(google_tests)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'Google_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "../src/*/*.h" "../src/*/*.cpp")
add_executable(Google_Tests_run
        test1.cpp
        ${sources}
        )
target_link_libraries(Google_Tests_run gtest gtest_main Qt5::Widgets box2d  ${SDL2PP_LIBRARIES})
