cmake_minimum_required(VERSION 3.16)

project(myProject)

# Set C++ standard to 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set the compiler to g++
set(CMAKE_CXX_COMPILER g++)

# autodesk maya
# For GitHub Actions cross-platform, use different paths for local and online builds
if (WIN32)
    set(MAYA_DEVKIT_PATH "dependencies/maya/devkitBase")
else()
    set(MAYA_DEVKIT_PATH "dependencies/maya/devkitBase")
endif()

include_directories(${MAYA_DEVKIT_PATH}/include)
link_directories(${MAYA_DEVKIT_PATH}/lib)

# autodesk fbx
# Downloaded and installed from: https://aps.autodesk.com/developer/overview/fbx-sdk
# Hardcoded paths for Windows and Linux
if (WIN32)
    set(FBX_DEVKIT_PATH "dependencies/fbx")
else()
    set(FBX_DEVKIT_PATH "dependencies/fbx")
endif()

include_directories(${FBX_DEVKIT_PATH}/include)
link_directories(${FBX_DEVKIT_PATH}/lib/vs2022/x64/release)

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

# Include directories for Python
include_directories(${Python_INCLUDE_DIRS})
link_directories(${Python_LIBRARY_DIRS})

# Test project
add_executable(myProject PythonCommands.cpp main.cpp)
target_link_libraries(myProject pybind11::embed)

target_link_libraries(myProject
    ZLIB::ZLIB
    Alembic::Alembic
    #glfw
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
    #libfbxsdk.lib
    pybind11::embed
    pybind11::module
    -Wl,-rpath, dependencies/maya/devkitBase
    -Wl,-rpath, dependencies/maya/devkitBase/include
    -Wl,-rpath, dependencies/maya/devkitBase/lib
    -Wl,-rpath, dependencies/maya/devkitBase/lib/Qt5
)

# Add a Python module, No need to link myPythonModule with myApp
pybind11_add_module(mush PythonCommands.cpp)
