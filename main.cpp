#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <zlib.h>
#include <Alembic/Abc/Base.h>
#include <Eigen/Dense>
#include <glm/glm.hpp>
#include <fmt/core.h>
#include <asio.hpp>
#include <nlohmann/json.hpp>
#include <curl/curl.h>
#include <maya/MVector.h>

int main() {
    // test zlib
    std::cout << "Zlib version: " << ZLIB_VERSION << std::endl;

    // test alembic
    std::cout << "Alembic Library Version: "
        << Alembic::Abc::GetLibraryVersion()
        << std::endl;

    // test eigen
    Eigen::Matrix4f M = Eigen::Matrix4f::Identity();
    std::cout << "Eigen Matrix:\n" << M << std::endl;

    // test glm
    glm::vec3 vec(1.0f, 2.0f, 3.0f);
    std::cout << "GLM Vector: " << vec.x << ", " << vec.y << ", " << vec.z << "\n";

    // test fmt
    std::string message = fmt::format("The answer is {}.", 42);
    std::cout << message << std::endl;

    // test asio
    try {
        asio::io_context io_context;
        std::cout << "ASIO initialized successfully." << std::endl;
    }
    catch (std::exception& e) {
        std::cerr << "Failed to initialize ASIO: " << e.what() << std::endl;
    }

    // test nlohmann
    nlohmann::json j;
    j["name"] = "John Doe";
    j["age"] = 30;
    j["is_programmer"] = true;
    std::cout << j << std::endl;

    // test lib curl
    CURL* curl = curl_easy_init();
    if (curl) {
        std::cout << "libcurl initialized successfully." << std::endl;
        curl_easy_cleanup(curl);
    }
    else {
        std::cerr << "Failed to initialize libcurl." << std::endl;
    }

    // test maya
    MVector mv(1, 2, 3);
    std::cout << "Maya Vector " << mv.x << ", " << mv.y << ", " << mv.z << std::endl;

    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    GLFWwindow* window = glfwCreateWindow(640, 480, "OpenGL Test", NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Load GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    std::cout << "OpenGL Version " << GLVersion.major << "." << GLVersion.minor << std::endl;
    std::cout << "GLAD and GLFW initialized successfully" << std::endl;

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}