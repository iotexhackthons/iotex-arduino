cmake_minimum_required(VERSION 3.10.0)

project(
    iotex-antenna-arduino-tests
    VERSION 1.0
    LANGUAGES CXX)
  
# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include")
endif()


set (IOTEX_UNIT_TESTS_SOURCES 
    src/api/wallets/walletsTests.cpp
)

add_executable(iotex_unit_tests
    ${IOTEX_UNIT_TESTS_SOURCES}
)

target_compile_definitions(iotex_unit_tests
    PRIVATE UNIT_TEST_BUILD
)

target_include_directories(iotex_unit_tests
    PUBLIC include
)

# Now simply link against gtest or gtest_main as needed
target_link_libraries(iotex_unit_tests 
    PRIVATE gtest
    PRIVATE gtest_main
    PRIVATE gmock
    PRIVATE curl
    PUBLIC iotex-antenna-arduino
)

add_test(
    NAME iotex_unit_tests
    COMMAND iotex_unit_tests
)
  
# Cmake 3.10
# gtest_discover_tests(iotex_unit_tests)

# Cmake 3.9
# gtest_add_tests(
#     iotex_unit_tests
#     ${IOTEX_UNIT_TESTS_SOURCES}
# )