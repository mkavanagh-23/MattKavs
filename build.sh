#!/bin/bash

# Build the library
cd build/
echo "Building C++ Library 'MattKavs'"
cmake ..
make

# Run the tests
echo "Running tests..."
ctest

# Install the library
if [ $? -eq 0 ]; then
  read -p "Would you like to install the library to your system? (y/n): " choice
  if [ "$choice" == "Y" ] || [ "$choice" == "y" ]; then
    sudo make install
  fi
fi
