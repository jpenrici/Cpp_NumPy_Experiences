#pragma once

#include <vector>

struct AnalysisResult {
    std::vector<double> normalizerd;
    std::vector<double> outliers;
};

class Calc {

public:
    auto normalize_minmax(const std::vector<double> &vec) -> std::vector<double>;

    auto detect_outliers_zscore(const std::vector<double> &vec, double threshold) -> std::vector<double>;

    auto analyse_vector(const std::vector<double> & vec, double threshold = 3.0) -> AnalysisResult;
};
