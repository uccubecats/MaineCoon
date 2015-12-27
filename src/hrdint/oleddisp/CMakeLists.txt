# Project details
project(oleddisp)

# Project Headers/Source
set(${PROJECT_NAME}_headers "${PARENT_DIR}/libs/wiringpi/wiringpi.h" "oleddisp.h")
set(${PROJECT_NAME}_sources "oleddisp.cpp")

# Create the library
add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_headers}
                                   ${${PROJECT_NAME}_sources})
target_link_libraries(${PROJECT_NAME} ${PYTHON_LIBRARIES})
target_link_libraries(${PROJECT_NAME} wiringpi)
