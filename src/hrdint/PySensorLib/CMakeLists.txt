# Project details
project(SensorLib)

# Project Headers/Source
set(${PROJECT_NAME}_headers "SensorLib.h")
set(${PROJECT_NAME}_sources "SensorLib.cpp")

# Create the library
add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_headers}
                                   ${${PROJECT_NAME}_sources})
target_link_libraries(${PROJECT_NAME} ${PYTHON_LIBRARIES})
