#include <pybind11/embed.h>

namespace py = pybind11;

// Example function to be exposed to Python
int add(int a, int b) {
    return a + b;
}

// Define the Python module
PYBIND11_MODULE(mush, m) {

    // Expose the 'add' function
    m.def("add", &add, "A function which adds two numbers");
}