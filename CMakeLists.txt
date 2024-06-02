cmake_minimum_required(VERSION 3.23)
project(c_graphics C)

set(CMAKE_C_STANDARD 23)

add_executable(c_graphics main.c colors.c canvas.c shapes.c triangle.c graphics.c)
