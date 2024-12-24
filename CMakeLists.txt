cmake_minimum_required(VERSION 3.14)
project(MoneyTracker)

set(CMAKE_CXX_COMPILER      "/usr/bin/clang++")
set(CXX_STANDARD 20)
set(FLAGS -Wall -Werror -Wpedantic -Wextra)

add_executable(${PROJECT_NAME} main.cpp)

target_compile_options(${PROJECT_NAME} PRIVATE ${FLAGS})
set_target_properties(${PROJECT_NAME}   PROPERTIES
                                        CXX_STANDARD 20
                                        CXX_STANDARD_REQUIRED ON)

