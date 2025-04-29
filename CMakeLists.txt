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

# Try to find system-installed Catch2 first
find_package(Catch2 3 REQUIRED CONFIG QUIET)

if(NOT Catch2_FOUND)
    message(STATUS "Catch2 not found, using FetchContent to download it")
    include(FetchContent)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.5.2
    )
    FetchContent_MakeAvailable(Catch2)
else()
    message(STATUS "Using system-installed Catch2")
endif()

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
# Install Rules
# -----------------------

# Install the library

# Set Linux install paths for the current distro
include(GNUInstallDirs)

# Install the targets
install(TARGETS MattKavs
    EXPORT MattKavsTargets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install public headers
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/MattKavs)

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

