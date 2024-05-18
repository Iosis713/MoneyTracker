cmake_minimum_required(VERSION 3.10)
project(MoneyTracker)

set(CXX_STANDARD REQUIRED 20)
set(FLAGS   -Wall -Wpedantic -Wextra -Werror)
set(SRC     Source/Transaction.cpp)

find_package(GTest REQUIRED)

add_library(${PROJECT_NAME}-lib     ${SRC})
add_executable(${PROJECT_NAME} main.cpp)
add_executable(TestRunner testRunner.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}-lib)

target_link_libraries(TestRunner PRIVATE ${GTEST_LIBRARIES}
                                         ${PROJECT_NAME}-lib
                                         pthread)

target_compile_options(${PROJECT_NAME}-lib PRIVATE ${FLAGS})
target_compile_options(${PROJECT_NAME} PRIVATE ${FLAGS})
target_compile_options(TestRunner PRIVATE ${FLAGS})


set_target_properties(${PROJECT_NAME}-lib   PROPERTIES
                                            CXX_STANDARD 20
                                            CXX_STANDARD_REQUIRED ON)

set_target_properties(${PROJECT_NAME}  PROPERTIES
                                       CXX_STANDARD 20
                                       CXX_STANDARD_REQUIRED ON)

set_target_properties(TestRunner   PROPERTIES
                                   CXX_STANDARD 20
                                   CXX_STANDARD_REQUIRED ON)

