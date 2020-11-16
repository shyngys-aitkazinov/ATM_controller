cmake_minimum_required(VERSION 3.0.0)
project(atm_controller VERSION 0.1.0)

include(CTest)
enable_testing()


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++17")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -lncurses")

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH  ${CMAKE_BINARY_DIR}/lib)
message(${CMAKE_BINARY_DIR})
# Build type - Release by default

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# # Includes
# include_directories(includes)

# # Project modules
# add_subdirectory(src)
set(SOURCES main.cpp 
            src/atm_controller.cpp 
            includes/atm_controller.hpp)

add_executable(atm_controller ${SOURCES} )