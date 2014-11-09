CMAKE_MINIMUM_REQUIRED(VERSION 2.8.4)

PROJECT(NIFConverter)

SET(SOURCE_FILES
    src/main.cpp
    src/Settings.cpp
    src/ResourceManager.cpp
    src/nif/Texture.cpp
    src/nif/Material.cpp
    src/nif/NifParser.cpp
    src/nif/SceneNode.cpp
    src/nif/SceneMesh.cpp
    src/nif/SceneNodeTransform.cpp
)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "C:/Users/plange.NLBERLIN/CLionProjects/demo/build")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")

ADD_COMPILE_OPTIONS(-std=c++0x)

INCLUDE_DIRECTORIES(include)
LINK_DIRECTORIES(lib)

ADD_EXECUTABLE(NIFConverter ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(NIFConverter niflib_static jsoncpp)