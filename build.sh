#!/usr/bin/env bash

echo "==================== Checking build directory..."
cd "$(dirname $0)"
mkdir -p build
cd build

echo "==================== Running CMake..."
cmake -DCMAKE_BUILD_TYPE=Debug ..
if [ $? -ne 0 ]; then
	exit 1
fi

echo "==================== Running Make..."
make
if [ $? -ne 0 ]; then
	exit 1
fi