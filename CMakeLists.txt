cmake_minimum_required(VERSION 3.10)
project(MoneyTracker)

set(CXX_STANDARD REQUIRED 20)
set(FLAGS   -Wall -Wpedantic -Wextra -Werror)

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)
add_executable(TestRunner testRunner.cpp)

target_link_libraries(TestRunner PRIVATE ${GTEST_LIBRARIES}
                                         pthread)

target_compile_options(${PROJECT_NAME} PRIVATE ${FLAGS})
target_compile_options(TestRunner PRIVATE ${FLAGS})


set_target_properties(${PROJECT_NAME}  PROPERTIES
                                       CXX_STANDARD 20
                                       CXX_STANDARD_REQUIRED ON)

set_target_properties(TestRunner   PROPERTIES
                                   CXX_STANDARD 20
                                   CXX_STANDARD_REQUIRED ON)

