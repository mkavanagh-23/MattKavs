cmake_minimum_required(VERSION 3.16)

project(MattKavs
    VERSION 1.0
    DESCRIPTION "A personal collection of useful functions and utilities"
    LANGUAGES CXX
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable CMake to generate the compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# --- Sources ---
file(GLOB_RECURSE LIB_SOURCES CONFIGURE_DEPENDS src/*.cpp)
file(GLOB_RECURSE LIB_HEADERS CONFIGURE_DEPENDS include/*.h)

add_library(MattKavs SHARED
    ${LIB_SOURCES}
    ${LIB_HEADERS}
)

target_include_directories(MattKavs PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# --- Tests ---
include(CTest)
enable_testing()

include(FetchContent)
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    GIT_TAG v3.5.2
)
FetchContent_MakeAvailable(Catch2)

file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS test/*.cpp)

add_executable(MattKavsTests
    ${TEST_SOURCES}
)

target_link_libraries(MattKavsTests
    PRIVATE
    MattKavs
    Catch2::Catch2WithMain
)

include(Catch)
catch_discover_tests(MattKavsTests)

# -----------------------
# Install Rules - New Part
# -----------------------

# Install the library
install(TARGETS MattKavs
    EXPORT MattKavsTargets
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

# Install public headers
install(DIRECTORY include/ DESTINATION include/MattKavs)

# Export a CMake package config for easy find_package
install(EXPORT MattKavsTargets
    FILE MattKavsTargets.cmake
    NAMESPACE MattKavs::
    DESTINATION lib/cmake/MattKavs
)

# Create a version file for the package (optional but nice)
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/MattKavsConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

# Install the config file
install(FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/MattKavsConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/MattKavsConfigVersion.cmake
    DESTINATION lib/cmake/MattKavs
)

