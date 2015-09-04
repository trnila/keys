cmake_minimum_required(VERSION 3.2)
set(Boost_USE_STATIC_LIBS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package( Boost REQUIRED COMPONENTS program_options )
INCLUDE(FindPkgConfig)
PKG_SEARCH_MODULE(SDL2 REQUIRED sdl2)

include_directories(
	${SDL2_INCLUDE_DIRS}
	${Boost_INCLUDE_DIRS}
)

set(SOURCE_FILES
	Audio.cpp
	Player.cpp
	AudioLoader.cpp
	Track.cpp
	Input/RawInput.cpp
	Input/Termios.cpp
	Input/Input.cpp
	Modes/ListenMode.cpp
	Modes/FeedbackMode.cpp
)

add_library(lib STATIC ${SOURCE_FILES})

add_executable(keyquiz keyquiz.cpp)
target_link_libraries(keyquiz lib ${SDL2_LIBRARIES})

add_executable(keyboardfeedback keyfeedback.cpp)
target_link_libraries(keyboardfeedback lib ${SDL2_LIBRARIES} ${Boost_PROGRAM_OPTIONS_LIBRARY})
