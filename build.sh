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

# Install the library
if [ $? -eq 0 ]; then
  read -p "Would you like to install the library to your system? (y/n): " choice
  if [[ "$choice" =~ ^[Yy]$ ]]; then
    sudo make install
  fi
fi
