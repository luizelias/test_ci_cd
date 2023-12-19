cmake_minimum_required(VERSION 3.0)
project(HelloWorld)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the path to the vcpkg toolchain file
if(EXISTS "/vcpkg/scripts/buildsystems/vcpkg.cmake")
    # Path in Docker environment
    set(CMAKE_TOOLCHAIN_FILE "/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file in Docker")
elseif(EXISTS "C:/vcpkg/scripts/buildsystems/vcpkg.cmake")
    # Path in local Windows environment
    set(CMAKE_TOOLCHAIN_FILE "C:/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file in Windows")
else()
    message(FATAL_ERROR "Vcpkg toolchain file not found. Please define CMAKE_TOOLCHAIN_FILE.")
endif()

# Find packages installed by vcpkg
find_package(Eigen3 CONFIG REQUIRED)
find_package(Alembic CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(asio CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

# Add your source files
add_executable(HelloWorld main.cpp)

# Link all libraries in a single command
target_link_libraries(HelloWorld PRIVATE 
    Eigen3::Eigen 
    Alembic::Alembic 
    fmt::fmt 
    glfw 
    glad::glad 
    asio asio::asio 
    nlohmann_json nlohmann_json::nlohmann_json)
