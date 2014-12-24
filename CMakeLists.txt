CMAKE_MINIMUM_REQUIRED(VERSION 2.8.4)

PROJECT(NIFConverter)

SET(SOURCE_FILES
    src/main.cpp
    src/utils/ConverterSettings.cpp
    src/utils/ResourceManager.cpp
    src/utils/LoggingManager.cpp
    src/nif/Texture.cpp
    src/nif/Material.cpp
    src/nif/NifParser.cpp
    src/nif/SceneNode.cpp
    src/nif/SceneMesh.cpp
    src/nif/SceneNodeTransform.cpp
)

# the name of the target operating system
SET(CMAKE_SYSTEM_NAME Windows)

# specify the cross compiler
SET(CMAKE_C_COMPILER   x86_64-w64-mingw32-gcc)
SET(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)
SET(CMAKE_RC_COMPILER x86_64-w64-mingw32-windres)

SET(CMAKE_CXX_FLAGS "-std=c++11 -static-libgcc -static-libstdc++ -static -O3 -s")
SET(CMAKE_C_FLAGS "-static-libgcc -static-libstdc++ -static -O3 -s")
SET(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "-static-libgcc -static-libstdc++ -static -O3 -s")
SET(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "-static-libgcc -static-libstdc++ -static -O3 -s")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build")

INCLUDE_DIRECTORIES(include)
LINK_DIRECTORIES(lib)

ADD_EXECUTABLE(NIFConverter.exe ${SOURCE_FILES})
TARGET_LINK_LIBRARIES(NIFConverter.exe niflib_static jsoncpp)