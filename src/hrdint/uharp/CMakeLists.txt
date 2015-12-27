# Project details
project(uharp)

# Project Headers/Source
set(${PROJECT_NAME}_headers "AprsPacketUtil.h")
set(${PROJECT_NAME}_sources "AprsPacketUtil.cpp")

# Create the library
add_library(${PROJECT_NAME} SHARED ${${PROJECT_NAME}_headers}
                                   ${${PROJECT_NAME}_sources})
