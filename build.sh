#!/bin/bash

# Build the library
mkdir build
cd build/
echo "Building C++ Library 'MattKavs'"

# Set install prefix to /usr to avoid needing -I /usr/local/include and -L /usr/local/lib
cmake -DCMAKE_INSTALL_PREFIX=/usr ..
make

# Run the tests
echo "Running tests..."
ctest
