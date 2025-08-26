cmake_minimum_required(VERSION 3.16)
project(DeclarativeUI CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add lvgl include directory
# This path might need to be adjusted based on your project structure
include_directories(../lvgl)

# Create a library for the declarative UI framework
add_library(DeclarativeUILib STATIC
    core/DuiObject.cpp
    core/DuiViewBase.cpp
    components/DuiText.cpp
    components/DuiButton.cpp
    layouts/DuiVStack.cpp
    layouts/DuiHStack.cpp
)

# Create an executable for the example
add_executable(DuiExample main.cpp)

# Add the declarative directory itself to the include path
target_include_directories(DeclarativeUILib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(DuiExample PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Link the example against the DeclarativeUI library and lvgl
# Assuming lvgl is a target library in the parent project
target_link_libraries(DuiExample PRIVATE DeclarativeUILib lvgl lvgl_thorvg)
