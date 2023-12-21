#include <pybind11/pybind11.h>
#include <string>

namespace py = pybind11;

// Example function to be exposed to Python
int add(int a, int b) {
    return a + b;
}

// Define the Python module
PYBIND11_MODULE(myPythonModule, m) {
    m.doc() = "pybind11 example plugin"; // Optional module docstring

    // Expose the 'add' function
    m.def("add", &add, "A function which adds two numbers");
}