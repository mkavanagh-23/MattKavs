## Build Instructions
### Step 1: Configure and build
cd your_project/
mkdir -p build && cd build
cmake ..
make

### Step 2: Install (might need sudo)
sudo make install

## Linking In Other Projects
find_package(YourLibraryName REQUIRED)
target_link_libraries(MyApp PRIVATE YourLibraryName::YourLibraryName)
