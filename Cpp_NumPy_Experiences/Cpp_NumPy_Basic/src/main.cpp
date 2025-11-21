#include "example.hpp"

#include <pybind11/embed.h>

#include <print>

namespace py = pybind11;

auto main() -> int {

  // Result: [110, 122, 133, 144]
  std::vector vec1{100.0, 101.1, 102.2, 103.3};
  std::vector vec2{10.0, 20.9, 30.8, 40.7};

  py::scoped_interpreter guard{};

  try {
    auto result = add(vec1, vec2);
    std::println("Result: {}", result);
  } catch (const std::exception &e) {
    std::println("Error: {}", e.what());
  }

  return 0;
}
