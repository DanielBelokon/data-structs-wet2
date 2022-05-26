cmake_minimum_required(VERSION 3.14)  # CMake version check
project(data-structs-wet2)            
set(CMAKE_CXX_STANDARD 11)            # Enable c++11 standard

add_compile_options (-std=c++11 -Wall -Wextra -Werror -Wno-unused-parameter)

# source directory
add_subdirectory(src)

if(BUILD_TESTING)
  add_subdirectory(tests)
endif()

