# Project details
project(wiringpi)

# Project Headers/Source
set(${PROJECT_NAME}_headers "wiringpi.h")
set(${PROJECT_NAME}_sources "wiringpi.cpp")

# Create the library
add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_headers}
                                   ${${PROJECT_NAME}_sources})
#target_link_libraries(${PROJECT_NAME} libname)
