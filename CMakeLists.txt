cmake_minimum_required(VERSION 3.23)
project(AGH_OOPL_ToDo_List_App)

set(CMAKE_CXX_STANDARD 20)

add_executable(AGH_OOPL_ToDo_List_App main.cpp TodoItem.cpp TodoItem.h Utils.cpp Utils.h Globals.cpp Globals.h)
