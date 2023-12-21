cmake_minimum_required(VERSION 3.15)

project(myProject)

# autodesk maya
# for github actions cross platform we need to modify this cmake code here
# to work on both my windows home setup and the online build on github (windows and centos 7.9)
# autodesk devikit can be downloaded at https://aps.autodesk.com/developer/overview/maya
set(MAYA_DEVKIT_PATH "C:/Program Files/Autodesk/Maya2019/devkitBase")
include_directories(${MAYA_DEVKIT_PATH}/include)
link_directories(${MAYA_DEVKIT_PATH}/lib)

# c++ 17
set(CMAKE_CXX_STANDARD 17)

# autodesk fbx
# it should be downloaded and installed from here: https://aps.autodesk.com/developer/overview/fbx-sdk
# this is the hardcoded windows installation
set(FBX_DEVKIT_PATH "C:/Program Files/Autodesk/FBX/FBX SDK/2020.3.4")
include_directories(${FBX_DEVKIT_PATH}/include)
link_directories(${FBX_DEVKIT_PATH}/lib/vs2022/x64/release)

# packages installed with vcpkg
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

# python
include_directories(${Python_INCLUDE_DIRS})
link_directories(${Python_LIBRARY_DIRS})

# test project
add_executable(myApp main.cpp PythonCommands.cpp)

target_link_libraries(myApp 
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
libfbxsdk.lib # on linux it will be different
pybind11::module
)

# Add a Python module, No need to link myPythonModule with myApp
pybind11_add_module(mush PythonCommands.cpp)