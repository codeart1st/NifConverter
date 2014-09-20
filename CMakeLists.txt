CMAKE_MINIMUM_REQUIRED(VERSION 2.8.4)

PROJECT(Demo)

SET(SOURCE_FILES
    main.cpp
    Settings.cpp
    Mesh.cpp
    Texture.cpp
    NifParser.cpp
)

ADD_COMPILE_OPTIONS(-std=c++0x)

INCLUDE_DIRECTORIES(include)
LINK_DIRECTORIES(lib)

ADD_EXECUTABLE(Demo ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(Demo niflib jsoncpp)