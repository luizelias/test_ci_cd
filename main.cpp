#include <glad/glad.h> // Glad must be included first
#include <GLFW/glfw3.h>

#include <Eigen/Dense>
#include <Alembic/AbcGeom/All.h>
#include <glm/glm.hpp>
#include <fmt/core.h>
#include <asio.hpp>
#include <nlohmann/json.hpp>

#include <iostream>
#include <thread>

int main()
{
    // Eigen test
    Eigen::MatrixXd m(2, 2);
    m(0, 0) = 3;
    m(1, 0) = 2.5;
    m(0, 1) = -1;
    m(1, 1) = m(1, 0) + m(0, 1);
    std::cout << "Eigen matrix:\n" << m << std::endl;

    // Alembic test (simple version string print)
    std::cout << "Alembic version: " << Alembic::AbcGeom::GetLibraryVersion() << std::endl;

    // GLM test
    glm::vec2 vec(1.0f, 2.0f);
    std::cout << "GLM vector: (" << vec.x << ", " << vec.y << ")" << std::endl;

    // fmt test
    std::string formatted = fmt::format("Formatted number: {}", 42);
    std::cout << formatted << std::endl;

    // GLFW test
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    std::cout << "GLFW initialized" << std::endl;
    glfwTerminate();

    // Glad test (dummy - normally used after a valid OpenGL context)
    std::cout << "Glad loaded (context not created, dummy test)" << std::endl;

    // Asio test
    asio::io_context io_context;
    asio::steady_timer t(io_context, asio::chrono::seconds(1));
    t.wait();
    std::cout << "Asio timer waited for 1 second" << std::endl;

    // nlohmann_json test
    nlohmann::json json;
    json["name"] = "Luiz";
    std::cout << "JSON example: " << json.dump() << std::endl;

    return 0;
}