cmake_minimum_required(VERSION 3.0.0)

# Project Specifics.
set(PROJECTNAME "MaineCoon")
project(${PROJECTNAME} CXX)

# Setup the project version.
SET(VERSION_MAJOR "1")
SET(VERSION_MINOR "0")
SET(VERSION_PATCH "0")
SET(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

# Global reference to the parent directory.
SET(PARENT_DIR "${CMAKE_CURRENT_SOURCE_DIR}" CACHE INTERNAL "Parent Directory")

# Add library include directories (their sub-directory).
#include_directories(LibDirName)

# Add project subdirectories.
add_subdirectory(hrdint)
#add_subdirectory(LibDirName)

# Create the executable.
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} hrdint)
#target_link_libraries(${PROJECT_NAME} LibName)

# Add custom build commands to execute.
add_custom_command(TARGET ${PROJECT_NAME} COMMAND java -jar ../utilities/DistPackage.jar)
