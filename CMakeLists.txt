cmake_minimum_required(VERSION 3.22.1)

project(myProject)

# Set C++ standard to 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the compiler to g++
set(CMAKE_CXX_COMPILER g++)

# Autodesk Maya
set(MAYA_DEVKIT_PATH "maya/devkitBase")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--copy-dt-needed-entries")

# Autodesk FBX
set(FBX_DEVKIT_PATH "D:/a/test_ci_cd/test_ci_cd/fbx")

# Link directories for Maya and Fbx
link_directories(
    maya/lib
    maya
    ${MAYA_DEVKIT_PATH}/lib
    ${MAYA_DEVKIT_PATH}/bin
    ${MAYA_DEVKIT_PATH}/devkit/bim
    ${MAYA_DEVKIT_PATH}/devkit/synColor/lib
    ${MAYA_DEVKIT_PATH}/devkit/ufe/lib
    ${MAYA_DEVKIT_PATH}/devkit/Alembic/lib
    ${MAYA_DEVKIT_PATH}/include
    ${MAYA_DEVKIT_PATH}/plug-ins
    ${MAYA_DEVKIT_PATH}/applications
    ${FBX_DEVKIT_PATH}/lib/gcc/x64/release
    ${FBX_DEVKIT_PATH}/include
    ${FBX_DEVKIT_PATH}/lib/vs2022/arm64/debug
    D:/a/test_ci_cd/test_ci_cd/fbx/lib/vs2022/arm64/debug
    /usr/lib/x86_64-linux-gnu
    /usr/lib/i386-linux-gnu
)

include_directories(
    ${MAYA_DEVKIT_PATH}/include
    ${FBX_DEVKIT_PATH}/include
    ${FBX_DEVKIT_PATH}/include/libxml2/libxml
)

# Link directories for Autodesk FBX
link_directories(${FBX_DEVKIT_PATH}/lib/gcc/x64/release)
include_directories(${FBX_DEVKIT_PATH}/include)
include_directories("D:/a/test_ci_cd/test_ci_cd/fbx/include/fbxsdk.h")

# Find packages installed with vcpkg
find_package(ZLIB REQUIRED)
find_package(Alembic CONFIG REQUIRED)
find_package(Eigen3 CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(asio CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(CURL REQUIRED)
find_package(Python COMPONENTS Interpreter Development REQUIRED)
find_package(pybind11 CONFIG REQUIRED)

# Test project
add_executable(myProject PythonCommands.cpp main.cpp)
target_link_libraries(myProject
    ZLIB::ZLIB
    Alembic::Alembic
    glfw
    glad::glad
    fmt::fmt-header-only
    asio::asio
    nlohmann_json::nlohmann_json
    CURL::libcurl
    OpenMaya
    OpenMayaAnim
    OpenMayaRender
    OpenMayaUI
    Foundation
    $<$<STREQUAL:$<PLATFORM_ID>,Windows>:libfbxsdk-md>
    $<$<STREQUAL:$<PLATFORM_ID>,Linux>:libfbxsdk.a>
    $<$<STREQUAL:$<PLATFORM_ID>,Linux>:xml2>
    pybind11::embed
    pybind11::module
)

# Add a Python module, No need to link myPythonModule with myApp
pybind11_add_module(mush PythonCommands.cpp)

# Set the specific paths for certain libraries using -rpath
if (WIN32)
else()
    set_target_properties(myProject PROPERTIES
        INSTALL_RPATH "$ORIGIN;/lib;/lib/x86_64-linux-gnu;/usr/lib;/usr/lib32;/usr/include;/usr/lib/aarch64-linux-gnu/android;/usr/lib/x86_64-linux-gnu"
        BUILD_WITH_INSTALL_RPATH TRUE
    )
endif()
