cmake_minimum_required(VERSION 3.14)
set(CMAKE_C_STANDARD 11)

set(ENVSDK $ENV{PLAYDATE_SDK_PATH})

if (NOT ${ENVSDK} STREQUAL "")
	# Convert path from Windows
	file(TO_CMAKE_PATH ${ENVSDK} SDK)
else()
	execute_process(
			COMMAND bash -c "egrep '^\\s*SDKRoot' $HOME/.Playdate/config"
			COMMAND head -n 1
			COMMAND cut -c9-
			OUTPUT_VARIABLE SDK
			OUTPUT_STRIP_TRAILING_WHITESPACE
	)
endif()

if (NOT EXISTS ${SDK})
	message(FATAL_ERROR "SDK Path not found; set ENV value PLAYDATE_SDK_PATH")
	return()
endif()

set(CMAKE_CONFIGURATION_TYPES "Debug;Release")
set(CMAKE_XCODE_GENERATE_SCHEME TRUE)

# Game Name Customization
set(PLAYDATE_GAME_NAME spelunky)
set(PLAYDATE_GAME_DEVICE spelunky_DEVICE)

project(${PLAYDATE_GAME_NAME} C ASM)

file(GLOB SRC_FILES 
	src/main.c
    game/src/util.c
    game/src/vector.c
    game/src/matrix.c
    game/src/context.c
    game/src/polygon.c
    game/src/font.c
    game/src/fastRandom.c
    game/src/entity.c
    game/src/map.c
    game/src/sprites.c
    game/src/data.c
    game/src/renderer.c
    game/src/game.c
    game/src/menu.c
    game/src/tests.c
    game/src/srcLevelGen.c
    game/src/srcRoomGen1.c
    game/src/characters/player.c
    game/src/characters/snake.c
)

if (TOOLCHAIN STREQUAL "armgcc")
	add_executable(${PLAYDATE_GAME_DEVICE}
		${SRC_FILES}
	)
	target_include_directories(${PLAYDATE_GAME_DEVICE} 
		PRIVATE
		./game/include
	)
else()
	add_library(${PLAYDATE_GAME_NAME} SHARED
	    ${SRC_FILES}
	)
	target_include_directories(${PLAYDATE_GAME_NAME} 
		PRIVATE
		./game/include
	)
endif()

include(${SDK}/C_API/buildsupport/playdate_game.cmake)

