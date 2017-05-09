#!/bin/bash

BUILD_EMU="OFF"
BUILD_SERVER="OFF"
BUILD_3DS="ON"
for arg in "$@"; do
    if [ "$arg" == "--with-emu" ]; then
		BUILD_EMU="ON"
	fi
    if [ "$arg" == "--with-server" ]; then
		BUILD_SERVER="ON"
	fi
    if [ "$arg" == "--without-3DS" ]; then
		BUILD_3DS="OFF"
	fi
done

mkdir -p build
cd build && cmake -DBUILD_EMULATOR=$BUILD_EMU -DBUILD_SERVER=$BUILD_SERVER -DBUILD_3DS=$BUILD_3DS ..
if [ $? -eq 1 ]; then # We try to remove and recreate the build, maybe because of CMakeCache
	cd .. && rm -r build
	mkdir -p build && cd build && cmake -DBUILD_EMULATOR=$BUILD_EMU -DBUILD_SERVER=$BUILD_SERVER -DBUILD_3DS=$BUILD_3DS ..
fi
if [ $? -eq 0 ]; then
	make -j4
fi

