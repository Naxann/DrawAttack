cmake_minimum_required(VERSION 2.8.11)

option(BUILD_EMULATOR "Build with cpp3ds emulator (Qt5 required)" OFF)
option(BUILD_SERVER "Build DrawAttack server" ON)
option(BUILD_3DS "Build 3DS DrawAttack" ON)

# Project name without spaces or special characters
project("DrawAttack")

set(APP_TITLE "DrawAttack")
set(APP_DESCRIPTION "Multiplayer drawing battle game.")
set(APP_AUTHOR "Naxann / Cruel")
set(APP_ICON ${PROJECT_SOURCE_DIR}/res/app/icon.png)
set(APP_LOGO ${PROJECT_SOURCE_DIR}/res/app/logo.bcma.lz)

# First one is Title Version, second is the readable version
set(APP_VERSION 14)
add_definitions(-DDRAWATTACK_VERSION="1.4.0a")
add_definitions(-DDRAWATTACK_DIR="sdmc:/3ds/data/drawattack")

# CIA settings
set(APP_UNIQUE_ID 0x7718) # This must be unique for your CIA project
set(APP_PRODUCT_CODE ${PROJECT_NAME})
set(BANNER_IMAGE ${PROJECT_SOURCE_DIR}/res/app/banner.png)
set(BANNER_SOUND ${PROJECT_SOURCE_DIR}/res/app/banner.wav)
set(CIA_CONFIG ${PROJECT_SOURCE_DIR}/res/app/cia.rsf)

# Include cpp3ds cmake module
set(CPP3DS $ENV{CPP3DS})
if(NOT CPP3DS)
	message(FATAL_ERROR "You need to set the env variable CPP3DS before compiling.")
endif()
set(CMAKE_MODULE_PATH "${CPP3DS}/cmake" ${CMAKE_MODULE_PATH})
if(BUILD_3DS)
	include(cpp3ds)

	include_directories(
		${PROJECT_SOURCE_DIR}/external/tween-engine/include
	)

	FILE(GLOB_RECURSE TWEEN_ENGINE_SOURCE ${PROJECT_SOURCE_DIR}/external/tween-engine/src/*.cpp)
endif()

set(SOURCE_FILES
	${PROJECT_SOURCE_DIR}/src/main.cpp
	${PROJECT_SOURCE_DIR}/src/DrawAttack.cpp
	${PROJECT_SOURCE_DIR}/src/DrawingBoard.cpp
	${PROJECT_SOURCE_DIR}/src/TweenTransformable.cpp
	${PROJECT_SOURCE_DIR}/src/SpeechBubble.cpp
	${PROJECT_SOURCE_DIR}/src/Notification.cpp
	${PROJECT_SOURCE_DIR}/src/ServerListItem.cpp
	${PROJECT_SOURCE_DIR}/src/ServerList.cpp
	${PROJECT_SOURCE_DIR}/src/ScoreBoard.cpp
	${PROJECT_SOURCE_DIR}/src/ChatLog.cpp
	${PROJECT_SOURCE_DIR}/src/RichText.cpp
	${PROJECT_SOURCE_DIR}/src/Util.cpp
	${PROJECT_SOURCE_DIR}/src/GUI/Button.cpp
	${PROJECT_SOURCE_DIR}/src/GUI/NinePatch.cpp
	${PROJECT_SOURCE_DIR}/src/Keyboard/Keyboard.cpp
	${PROJECT_SOURCE_DIR}/src/Keyboard/tinyxml2.cpp
	${PROJECT_SOURCE_DIR}/src/States/StateStack.cpp
	${PROJECT_SOURCE_DIR}/src/States/State.cpp
	${PROJECT_SOURCE_DIR}/src/States/TitleState.cpp
	${PROJECT_SOURCE_DIR}/src/States/ServerSelectState.cpp
	${PROJECT_SOURCE_DIR}/src/States/PlayState.cpp
	${PROJECT_SOURCE_DIR}/src/States/PauseState.cpp
	${PROJECT_SOURCE_DIR}/src/States/TransitionMessageState.cpp
	${PROJECT_SOURCE_DIR}/src/States/NameSelectState.cpp
	${PROJECT_SOURCE_DIR}/src/States/LoadingState.cpp
	${PROJECT_SOURCE_DIR}/src/States/ColorPickerState.cpp
	${PROJECT_SOURCE_DIR}/src/Network/Client.cpp
	${PROJECT_SOURCE_DIR}/src/Network/Player.cpp
	${PROJECT_SOURCE_DIR}/src/Network/NetworkEvents.cpp
	${PROJECT_SOURCE_DIR}/src/Network/NetworkSoundRecorder.cpp
	${PROJECT_SOURCE_DIR}/src/Network/NetworkSoundStream.cpp
	${TWEEN_ENGINE_SOURCE}
)
set(SERVER_SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/src/server.cpp
    ${PROJECT_SOURCE_DIR}/src/Network/Server.cpp
    ${PROJECT_SOURCE_DIR}/src/Network/ServerConfig.cpp
    ${PROJECT_SOURCE_DIR}/src/Network/Player.cpp
    ${PROJECT_SOURCE_DIR}/src/Network/NetworkEvents.cpp
	${PROJECT_SOURCE_DIR}/src/Keyboard/tinyxml2.cpp
)

if (BUILD_3DS)
	set(SHADER_AS nihstro)
	FILE(GLOB_RECURSE SHADER_FILES ${PROJECT_SOURCE_DIR}/res/shaders/[^.]*)
endif()

# Server target

if (BUILD_SERVER)
	include_directories(${CPP3DS}/include)
	link_directories(${CPP3DS}/lib)
	add_executable(${PROJECT_NAME}-server ${SERVER_SOURCE_FILES})
	set_target_properties(${PROJECT_NAME}-server PROPERTIES COMPILE_DEFINITIONS "EMULATION")
	set_target_properties(${PROJECT_NAME}-server PROPERTIES COMPILE_FLAGS "-std=c++11")
	target_link_libraries(${PROJECT_NAME}-server cpp3ds-emu sfml-system ssl crypto fmt)
endif()
##################################################
# Don't usually need to change anything below
##################################################
set(CPP3DS_ARM_FLAGS "-O2 -fno-rtti -fno-exceptions -march=armv6k -mtune=mpcore -mfloat-abi=hard -mtp=soft")
set(CPP3DS_EMU_FLAGS "-O0")

if(BUILD_3DS)
	include_directories(${DEVKITPRO}/portlibs/armv6k/include)
	set(CPP3DS_ARM_LIBS cpp3ds-window cpp3ds-graphics cpp3ds-audio cpp3ds-network cpp3ds-system citro3d mbedtls mbedx509 mbedcrypto ctru freetype png z vorbisenc vorbisfile vorbis ogg bz2 speex speexdsp fmt)
	set(CPP3DS_EMU_LIBS cpp3ds-emu sfml-graphics sfml-window sfml-system sfml-network sfml-audio openal GLEW GL jpeg freetype vorbisenc vorbisfile vorbis ogg ssl crypto pthread speex speexdsp fmt)
	add_subdirectory(${CPP3DS}/cmake/template_arm build/arm)
endif()

if(BUILD_EMULATOR)
	add_subdirectory(${CPP3DS}/cmake/template_emu build/emu)
endif()
