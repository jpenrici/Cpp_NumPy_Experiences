#pragma once

#include <vector>

struct AnalysisResult {
    std::vector<double> normalized;
    std::vector<double> outliers;
};

class Calc {

public:
    /**
     * @brief normalize_minmax
     * Min-Max normalization (or min-max scaling) is a data preprocessing technique
     * that transforms the values ​​of an array into a new range, usually between 0 and 1.
     *
     * @param vector<double>
     * @return vector<double>
     */
    auto normalize_minmax(const std::vector<double> &vec) const -> std::vector<double>;


    /**
     * @brief detect_outliers_zscore
     * Detecting outliers with Z-scores means standardizing the data
     * and checking which values ​​are far from the mean,
     * using standard deviations as a reference.
     *
     * @param vector<double>
     * @param threshold
     * @return vector<double>
     */
    auto detect_outliers_zscore(const std::vector<double> &vec, double threshold = 3.0) const -> std::vector<double>;

    auto analyse_vector(const std::vector<double> & vec, double threshold = 3.0) const -> AnalysisResult;
};
