# 'Google_test' is the subproject name
project(google_tests)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# 'Google_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "../src/*/*.h" "../src/*/*.cpp")

enable_testing()

# Create the executable
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
        COMMAND gcov -b ${CMAKE_SOURCE_DIR}/*.cpp -o ${OBJECT_DIR}
        | grep -A 5 "test1.cpp" > CoverageSummary.tmp
        COMMAND cat CoverageSummary.tmp
        COMMAND echo "-- Coverage files have been output to ${CMAKE_BINARY_DIR}/coverage"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/coverage
        )
add_dependencies(gcov Google_Tests_run)
# Make sure to clean up the coverage folder
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES coverage)

# Create the gcov-clean target. This cleans the build as well as generated
# .gcda and .gcno files.
add_custom_target(scrub
        COMMAND ${CMAKE_MAKE_PROGRAM} clean
        COMMAND rm -f ${OBJECT_DIR}/*.gcno
        COMMAND rm -f ${OBJECT_DIR}/*.gcda
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        )

# Testing
enable_testing()

include(GoogleTest)
gtest_discover_tests(Google_Tests_run Protocolo)
