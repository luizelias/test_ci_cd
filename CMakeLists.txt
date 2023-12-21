cmake_minimum_required(VERSION 3.0)

project(myProject)

# autodesk maya
# for github actions cross platform we need to modify this cmake code here
# to work on both my windows home setup and the online build on github (windows and centos 7.9)
# autodesk devikit can be downloaded at https://aps.autodesk.com/developer/overview/maya
set(MAYA_DEVKIT_PATH "C:/Program Files/Autodesk/Maya2019/devkitBase")
include_directories(${MAYA_DEVKIT_PATH}/include)
link_directories(${MAYA_DEVKIT_PATH}/lib)

message("${MAYA_DEVKIT_PATH}/lib")

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

# test project
add_executable(myProject main.cpp)

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
)

