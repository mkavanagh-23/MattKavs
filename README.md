## Build Instructions
### Step 1: Configure and build
```
cd build/
cmake ..
make
ctest
```

### Step 2: Install (might need sudo)
```
sudo make install
```

## Linking In Other Projects
```
find_package(MattKavs REQUIRED)
target_link_libraries(MyApp PRIVATE MattKavs::MattKavs)
```
