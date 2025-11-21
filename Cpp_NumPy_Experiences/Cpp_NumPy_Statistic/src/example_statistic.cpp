#include "example_statistic.hpp"

#include <pybind11/embed.h>
#include <pybind11/numpy.h>
#include <pybind11/pybind11.h>

#include <vector>

namespace py = pybind11;

auto Calc::normalize_minmax(const std::vector<double> &vec) const
    -> std::vector<double> {
  py::module np = py::module::import("numpy");

  py::array_t<double> arr(vec.size(), vec.data());

  auto min = np.attr("min")(arr);
  auto max = np.attr("max")(arr);

  py::array_t<double> np_result =
      (arr - min).cast<py::array>() / (max - min).cast<py::array>();

  std::vector<double> result(np_result.size());
  std::ranges::copy(np_result.data(), np_result.data() + np_result.size(),
                    result.begin());
  return result;
}

auto Calc::detect_outliers_zscore(const std::vector<double> &vec,
                                  double threshold) const
    -> std::vector<double> {
  py::module np = py::module::import("numpy");

  py::array_t<double> arr(vec.size(), vec.data());

  auto mean = np.attr("mean")(arr);
  auto std = np.attr("std")(arr);

  // z = |(x - mean) / std|
  py::array z =
      np.attr("abs")((arr - mean).cast<py::array>() / std.cast<py::array>());

  // mask = z > threshold
  py::array mask = np.attr("greater")(z, threshold);

  // arr[mask]
  py::array_t<double> np_result = arr.attr("__getitem__")(mask);

  std::vector<double> result(np_result.size());
  std::ranges::copy(np_result.data(), np_result.data() + np_result.size(),
                    result.begin());
  return result;
}

auto Calc::analyse_vector(const std::vector<double> &vec,
                          double threshold) const -> AnalysisResult {
  AnalysisResult r;
  r.normalized = normalize_minmax(vec);
  r.outliers = detect_outliers_zscore(vec, threshold);
  return r;
}
