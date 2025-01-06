cmake_minimum_required(VERSION 3.14)
project(MoneyTracker)

set(CMAKE_CXX_COMPILER      "/usr/bin/clang++")
set(CXX_STANDARD 20)
set(FLAGS -Wall -Werror -Wpedantic -Wextra)

set(SRC     ../Source/Category.cpp
            ../Source/Transaction.cpp
            ../Source/TransactionsManager.cpp
            ../Source/Printer.cpp
            ../Source/FileManager.cpp
            ../Source/Menu.cpp)

set(GMOCK_LIBRARIES /usr/lib/libgmock.a  /usr/lib/libgmock_main.a)
            
find_package(GTest REQUIRED)

add_library(${PROJECT_NAME}-lib     ${SRC})
add_executable(${PROJECT_NAME} main.cpp)
add_executable(${PROJECT_NAME}-gt   testRunner.cpp)

target_link_libraries(${PROJECT_NAME}       PRIVATE     ${PROJECT_NAME}-lib)
target_link_libraries(${PROJECT_NAME}-gt    PRIVATE     ${PROJECT_NAME}-lib
                                                        ${GTEST_LIBRARIES}
                                                        ${GMOCK_LIBRARIES}
                                                        pthread)

target_compile_options(${PROJECT_NAME}-lib  PRIVATE ${FLAGS})
target_compile_options(${PROJECT_NAME}      PRIVATE ${FLAGS})
target_compile_options(${PROJECT_NAME}-gt   PRIVATE ${FLAGS})

set_target_properties(${PROJECT_NAME}-lib   PROPERTIES
                                            CXX_STANDARD 20
                                            CXX_STANDARD_REQUIRED ON)

set_target_properties(${PROJECT_NAME}       PROPERTIES
                                            CXX_STANDARD 20
                                            CXX_STANDARD_REQUIRED ON)

set_target_properties(${PROJECT_NAME}-gt    PROPERTIES
                                            CXX_STANDARD 20
                                            CXX_STANDARD_REQUIRED ON)

