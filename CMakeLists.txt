cmake_minimum_required(VERSION 3.2)
project(key)

set(Boost_USE_STATIC_LIBS ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    main.cpp)

add_executable(key ${SOURCE_FILES} Audio.cpp Audio.h Player.cpp Player.h AudioLoader.cpp AudioLoader.h Track.cpp Track.h Input/RawInput.cpp Input/RawInput.h Input/Termios.cpp Input/Termios.h Input/Input.cpp Input/Input.h Modes/ListenMode.cpp Modes/ListenMode.h Modes/FeedbackMode.cpp Modes/FeedbackMode.h Modes/Mode.h)

find_package( Boost REQUIRED COMPONENTS program_options )

INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

INCLUDE_DIRECTORIES(
	${SDL2_INCLUDE_DIRS}
	${Boost_INCLUDE_DIRS}
)
TARGET_LINK_LIBRARIES(
	${PROJECT_NAME}
	${SDL2_LIBRARIES}
	${Boost_PROGRAM_OPTIONS_LIBRARY}
)

