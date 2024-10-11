cmake_minimum_required(VERSION 3.10)

# Set the project name
project(BoozyBingo)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(BoozyBingo main.cpp)
add_executable(Window window.cpp)

find_package(wxWidgets REQUIRED gl core base)
include(${wxWidgets_USE_FILE})
target_link_libraries(Window ${wxWidgets_LIBRARIES})

# Set the include and link directories
include(${wxWidgets_USE_FILE})
