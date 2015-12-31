# Project details
project(tempPress)

# Project Headers/Source
set(${PROJECT_NAME}_headers "${PARENT_DIR}/libs/wiringpi/wiringpi.h" "tempPress.h")
set(${PROJECT_NAME}_sources "tempPress.cpp")

# Create the library
add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_headers}
                                   ${${PROJECT_NAME}_sources})
target_link_libraries(${PROJECT_NAME} wiringpi)
