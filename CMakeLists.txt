cmake_minimum_required(VERSION 3.10)

# Set the project name
project(BoozyBingo)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find the wxWidgets package
find_package(wxWidgets REQUIRED COMPONENTS core base)

# Set the include and link directories
include(${wxWidgets_USE_FILE})

# Add the executable
add_executable(BoozyBingo main.cpp)

# Link wxWidgets libraries
target_link_libraries(BoozyBingo ${wxWidgets_LIBRARIES})
