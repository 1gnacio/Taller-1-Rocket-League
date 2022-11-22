# 'Google_test' is the subproject name
project(google_tests)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -fprofile-arcs -ftest-coverage")
set (CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)

# Create OBJECT_DIR variable
set(OBJECT_DIR ${CMAKE_BINARY_DIR}/google_tests/CMakeFiles/Google_Tests_run.dir)
message("-- Object files will be output to: ${OBJECT_DIR}")

# 'Google_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "../src/*/*.h" "../src/*/*.cpp")

add_executable(Google_Tests_run
        protocolo.cpp
        serializacion.cpp
        fisicas.cpp
        logica.cpp
        ${sources}
        )
target_link_libraries(
        Google_Tests_run gtest gtest_main Qt5::Widgets box2d  ${SDL2PP_LIBRARIES}
)

# Create the gcov target. Run coverage tests with 'make gcov'
add_custom_target(gcov
        COMMAND mkdir -p coverage
        COMMAND ${CMAKE_MAKE_PROGRAM} test
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )
add_custom_command(TARGET gcov
        COMMAND echo "=================== GCOV ===================="
        COMMAND gcov -b ${CMAKE_SOURCE_DIR}/google_tests/*.cpp -o ${OBJECT_DIR}
        COMMAND echo "-- Coverage files have been output to ${CMAKE_BINARY_DIR}/coverage"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/coverage
        )
add_dependencies(gcov Google_Tests_run)
# Make sure to clean up the coverage folder
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES coverage)

add_custom_target(scrub
        COMMAND ${CMAKE_MAKE_PROGRAM} clean
        COMMAND rm -f ${OBJECT_DIR}/*.gcno
        COMMAND rm -f ${OBJECT_DIR}/*.gcda
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )

enable_testing()

include(GoogleTest)

gtest_discover_tests(Google_Tests_run)