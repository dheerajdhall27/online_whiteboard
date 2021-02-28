# Your CMakeLists.txt for the main App project
# This time what is new is I have added:
# 1.) another 'add_executable'
# 2.) another 'target_link_libraries'
#
# Observe now you will have two projects setup.
# As they stand, they will be identical.
####################################################
# The minimum required version of CMake to ouse
cmake_minimum_required(VERSION 3.10)

# Set the project name to your project name
project(App)
set (CMAKE_CXX_STANDARD 11)

# find_package(SFML 2.5 COMPONENTS system window graphics network REQUIRED)
find_package(OpenGL REQUIRED)
# find_package(Catch2 REQUIRED)
include_directories("/usr/local/include/")
include_directories("/usr/include/")
include_directories("./include/")

link_directories("/usr/local/lib/")

# Add the source code files to a specific project
# We can indeed have multiple executables generated from
# one CMakeLists.txt file.
# For example, we might have test files that we want
# to generate.
add_executable(App ./src/App.cpp src/command/Command.cpp src/command/DrawCommand.cpp src/command/Pixel.cpp src/command/DataPacket.cpp src/networking/Server.cpp
        src/networking/Client.cpp src/networking/NetworkManagerFactory.cpp ./src/AppEventHandler.cpp src/gui/GUI.cpp src/command/DrawCircleCommand.cpp
        src/command/DrawSpraypaint.cpp src/command/DrawDiagonalLineCommand.cpp src/command/DrawHeartCommand.cpp src/command/DrawSquareCommand.cpp src/command/DrawRectCommand.cpp
        ./src/main.cpp)
target_link_libraries(App sfml-graphics sfml-window sfml-system sfml-network OpenGL::GL)
# target_include_directories(App PRIVATE include/)

add_executable(App_Test ./src/App.cpp src/command/Command.cpp src/command/Pixel.cpp src/command/DrawCommand.cpp src/command/DataPacket.cpp
        src/networking/Client.cpp src/networking/NetworkManagerFactory.cpp src/networking/Server.cpp ./src/AppEventHandler.cpp src/gui/GUI.cpp
        src/command/DrawSpraypaint.cpp src/command/DrawDiagonalLineCommand.cpp src/command/DrawCircleCommand.cpp src/command/DrawHeartCommand.cpp
        src/command/DrawSquareCommand.cpp src/command/DrawRectCommand.cpp ./tests/main_test.cpp)

# Add any libraries
# On linux, you can use the handy 'apt-file' tool to find
# where exactly header files exist. See example below:
# 	sudo apt install apt-file
#   	sudo apt-file update
# 	apt-file find Texture.hpp
target_link_libraries(App_Test sfml-graphics sfml-window sfml-system sfml-network OpenGL::GL)
# target_include_directories(App_Test
#    PRIVATE
#        include/
#)