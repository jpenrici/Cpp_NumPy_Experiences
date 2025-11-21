#include "example.hpp"

#include <pybind11/embed.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

#include <print>

namespace py = pybind11;

auto add(const std::vector<double> &vec1, const std::vector<double> &vec2)
    -> std::vector<double> {

  // NumPy
  py::module np = py::module::import("numpy");

  py::array_t<double> np_result =
      np.attr("add")(py::array_t<double>(vec1.size(), vec1.data()),
                     py::array_t<double>(vec2.size(), vec2.data()));

  std::vector<double> result(np_result.size());
  std::ranges::copy(np_result.data(), np_result.data() + np_result.size(),
                    result.begin());

  return result;
}
