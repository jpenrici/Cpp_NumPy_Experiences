#include "example_statistic.hpp"

#include <pybind11/embed.h>

#include <format>
#include <print>

namespace py = pybind11;

auto main() -> int {

  py::scoped_interpreter guard{};

  std::vector<double> data = {
      10,  12, 12, 13, 12, 11, 10, 9, 13,
      150, // outlier
      12,  11, 12, 8,  7,
      300 // outlier
  };

  try {
    const Calc calc;
    auto result = calc.analyse_vector(data, 1.4);
    std::println("Original data: {}", data);

    std::print("Normalized data: [");
    for (std::size_t i = 0; i < result.normalized.size(); ++i) {
      std::print("{:.3f}", result.normalized[i]);
      if (i + 1 < result.normalized.size()) {
        std::print(", ");
      }
    }
    std::println("]");

    std::println("Outliers detected: {}", result.outliers);
  } catch (const std::exception &e) {
    std::println("Error: {}", e.what());
  }

  return 0;
}
