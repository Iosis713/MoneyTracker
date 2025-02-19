cmake_minimum_required(VERSION 3.26)
project(MoneyTracker)

set(CMAKE_CXX_COMPILER      "/usr/bin/clang++-18")
set(FLAGS -Wall -Werror -Wpedantic -Wextra -std=c++20 -fmodules -Wno-experimental-header-units)

set(SRC     ../Source/Category.cpp
            ../Source/Transaction.cpp
            ../Source/TransactionsManager.cpp
            ../Source/Printer.cpp
            ../Source/FileManager.cpp
            ../Source/Menu.cpp)

set(GMOCK_LIBRARIES /usr/lib/libgmock.a  /usr/lib/libgmock_main.a)

set(PRECOMPILED_STL -fmodule-file=../Source/Modules/algorithm.pcm
                    -fmodule-file=../Source/Modules/chrono.pcm
                    -fmodule-file=../Source/Modules/concepts.pcm
                    -fmodule-file=../Source/Modules/fstream.pcm
                    -fmodule-file=../Source/Modules/iostream.pcm
                    -fmodule-file=../Source/Modules/memory.pcm
                    -fmodule-file=../Source/Modules/ranges.pcm
                    -fmodule-file=../Source/Modules/string.pcm
                    -fmodule-file=../Source/Modules/stdexcept.pcm
                    -fmodule-file=../Source/Modules/thread.pcm
                    -fmodule-file=../Source/Modules/tuple.pcm
                    -fmodule-file=../Source/Modules/type_traits.pcm
                    -fmodule-file=../Source/Modules/utility.pcm
                    -fmodule-file=../Source/Modules/vector.pcm)
            
find_package(GTest REQUIRED)

add_library(${PROJECT_NAME}-lib     ${SRC})
add_executable(${PROJECT_NAME} main.cpp)
add_executable(${PROJECT_NAME}-gt   testRunner.cpp)

target_link_libraries(${PROJECT_NAME}       PRIVATE     ${PROJECT_NAME}-lib)
target_link_libraries(${PROJECT_NAME}-gt    PRIVATE     ${PROJECT_NAME}-lib
                                                        ${GTEST_LIBRARIES}
                                                        ${GMOCK_LIBRARIES}
                                                        pthread)

target_compile_options(${PROJECT_NAME}-lib  PRIVATE ${FLAGS} ${PRECOMPILED_STL})
target_compile_options(${PROJECT_NAME}      PRIVATE ${FLAGS} ${PRECOMPILED_STL})
target_compile_options(${PROJECT_NAME}-gt   PRIVATE ${FLAGS} ${PRECOMPILED_STL})

set_target_properties(${PROJECT_NAME}-lib   PROPERTIES
                                            CXX_STANDARD 20
                                            CXX_STANDARD_REQUIRED ON)

set_target_properties(${PROJECT_NAME}       PROPERTIES
                                            CXX_STANDARD 20
                                            CXX_STANDARD_REQUIRED ON)

set_target_properties(${PROJECT_NAME}-gt    PROPERTIES
                                            CXX_STANDARD 20
                                            CXX_STANDARD_REQUIRED ON)

