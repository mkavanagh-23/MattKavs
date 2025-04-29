#!/bin/bash

cd build/
echo "Building C++ Library 'MattKavs'"
cmake ..
make

echo "Running tests..."
ctest
