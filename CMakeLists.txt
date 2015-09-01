cmake_minimum_required(VERSION 3.2)
project(key)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    main.cpp)

add_executable(key ${SOURCE_FILES} Audio.cpp Audio.h Player.cpp Player.h AudioLoader.cpp AudioLoader.h Track.cpp Track.h RawInput.cpp RawInput.h)

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)
INCLUDE_DIRECTORIES(${SDL2_INCLUDE_DIRS})
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${SDL2_LIBRARIES})
