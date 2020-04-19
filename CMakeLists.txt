cmake_minimum_required(VERSION 3.10)

# flags for debug build
set(CMAKE_C_FLAGS "-Wall -g -fsanitize=address")
add_definitions("-DLOGGING_BITMASK=7")

# flags for pref build
#set(CMAKE_CXX_FLAGS "-O2 ")
#add_definitions("-DLOGGING_BITMASK=4")

include_directories(${PROJECT_SOURCE_DIR})
include_directories(include/)

file(GLOB ATM_SRC atm_src/*.c)
file(GLOB CTRL_SRC atm_controller_src/*.c)

add_executable(atm ${ATM_SRC})
add_executable(atm_controller ${CTRL_SRC})
