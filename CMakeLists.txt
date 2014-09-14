cmake_minimum_required(VERSION 2.8.4)

project(Demo)

set(SOURCE_FILES main.cpp Settings.cpp Mesh.cpp Texture.cpp)

include_directories(include)
link_directories(lib)

add_executable(Demo ${SOURCE_FILES})

target_link_libraries(Demo niflib)
target_link_libraries(Demo SOIL)