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
SET(CMAKE_CXX_FLAGS "-pthread -I/usr/local/include -L/usr/local/lib -lwiringPi")

# Copy all required Files over.
file(COPY ${PARENT_DIR}/hrdint/oleddisp/pyoleddisp.py DESTINATION ${PARENT_DIR}/../build/hrdint/oleddisp)
file(COPY ${PARENT_DIR}/hrdint/oleddisp/SSD1306.py DESTINATION ${PARENT_DIR}/../build/hrdint/oleddisp)
file(COPY ${PARENT_DIR}/hrdint/oleddisp/Adafruit_GPIO DESTINATION ${PARENT_DIR}/../build/hrdint/oleddisp)
file(COPY ${PARENT_DIR}/hrdint/slowscan/pyslowscan.py DESTINATION ${PARENT_DIR}/../build/hrdint/slowscan)
file(COPY ${PARENT_DIR}/hrdint/slowscan/pysstv DESTINATION ${PARENT_DIR}/../build/hrdint/slowscan)

# Find all required external/third-party libraries.
find_package(PythonLibs REQUIRED)

# Add library include directories (their sub-directory).
include_directories(${PYTHON_INCLUDE_DIRS})

# Add project subdirectories.
add_subdirectory(libs/wiringpi)
add_subdirectory(hrdint/oleddisp)
add_subdirectory(hrdint/tempPress)
add_subdirectory(hrdint/slowscan)
add_subdirectory(hrdint/uharp)

# Create the executable.
add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} oleddisp)
target_link_libraries(${PROJECT_NAME} tempPress)
target_link_libraries(${PROJECT_NAME} slowscan)
target_link_libraries(${PROJECT_NAME} uharp)
target_link_libraries(${PROJECT_NAME} ${PYTHON_LIBRARIES})

# Add custom build commands to execute.
add_custom_command(TARGET ${PROJECT_NAME} COMMAND java -jar ../utilities/DistPackage.jar hrdint/oleddisp hrdint/slowscan)
