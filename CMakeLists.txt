CMAKE_MINIMUM_REQUIRED(VERSION 2.8.4)

PROJECT(NIFConverter)

SET(SOURCE_FILES
    main.cpp
    Settings.cpp
    Mesh.cpp
    Texture.cpp
    NifParser.cpp
    Material.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "/home/plange/ClionProjects/NIFConverter/build")

ADD_COMPILE_OPTIONS(-std=c++0x)

INCLUDE_DIRECTORIES(include)
LINK_DIRECTORIES(lib)

ADD_EXECUTABLE(NIFConverter ${SOURCE_FILES})

TARGET_LINK_LIBRARIES(NIFConverter niflib jsoncpp)