# Project details
project(slowscan)

# Project Headers/Source
set(${PROJECT_NAME}_headers "slowscan.h")
set(${PROJECT_NAME}_sources "slowscan.cpp")

# Create the library
add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_headers}
                                   ${${PROJECT_NAME}_sources})
target_link_libraries(${PROJECT_NAME} ${PYTHON_LIBRARIES})
