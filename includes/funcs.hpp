#ifndef FUNCS_H
#define FUNCS_H

#include <vector>
#include <utility>
#include <concepts>
#include <math.h>

template<typename T, int terms = 3>
inline T arcsin(T x) {
    T res = x;
    T x_squared = x * x;
    T current_power = x;
    
    double numerator = 1.0;
    double denominator = 1.0;
    
    for (int n = 1; n <= terms; ++n) {
        numerator *= (2*n - 1);
        denominator *= 2*n;
        current_power *= x_squared;
        res += current_power * (numerator / denominator) / (2*n + 1);
    }
    return res;
}

template<typename T>
concept has_eval = requires(const T& t) {
    { t.eval() } -> std::convertible_to<double>;
};

template<typename T = real128, typename Output = double, int terms = 20>
auto generate_arcsin_points(size_t num_points = 100) {
    std::vector<Output> x_vals, y_vals;
    x_vals.reserve(num_points + 1);
    y_vals.reserve(num_points + 1);

    const Output x_min = -0.99999;
    const Output x_max = 0.99999;
    const Output dx = (x_max - x_min) / num_points;

    for (size_t i = 0; i <= num_points; ++i) 
    {
        Output x = x_min + i * dx;
        T y = arcsin<T, terms>(T(x));
        x_vals.push_back(x);
        
        if constexpr (has_eval<T>) y_vals.push_back(y.eval()); 
        else y_vals.push_back(static_cast<Output>(y));
    }
    
    return std::make_pair(x_vals, y_vals);
}

template<typename T>
concept is_float = std::is_same_v<T, float>;

template<typename T>
auto generate_reference_points(size_t num_points=100)
{
    std::vector<T> x_vals, y_vals;
    x_vals.reserve(num_points + 1);
    y_vals.reserve(num_points + 1);

    const T x_min = -0.99999;
    const T x_max = 0.99999;
    const T dx = (x_max - x_min) / num_points;

    for (size_t i = 0; i <= num_points; ++i) 
    {
        T x = x_min + i * dx;
        T y;

        if (is_float<T>) y = asinf(x);
        else y = asin(x);

        x_vals.push_back(x);
        y_vals.push_back(y);
    }
    
    return std::make_pair(x_vals, y_vals);
}

template<typename T>
auto calculate_relative_error(std::vector<T> approximation, std::vector<T> expectation)
{
    std::vector<T> relative_error;

    size_t points_num = std::max(approximation.size(), expectation.size());

    for (size_t i = 0; i < points_num; ++i)
    {   
        auto error = std::abs((approximation[i] - expectation[i]) / expectation[i]);
        relative_error.emplace_back(error);
    }

    return relative_error;
}

template<typename T>
auto calculate_absolute_error(std::vector<T> approximation, std::vector<T> expectation)
{
    std::vector<T> absolute_error;

    size_t points_num = std::max(approximation.size(), expectation.size());

    for (size_t i = 0; i < points_num; ++i)
    {   
        auto error = std::abs(approximation[i] - expectation[i]);
        absolute_error.emplace_back(error);
    }

    return absolute_error;
}

auto calculate_diff(std::vector<double> a, std::vector<double> b)
{
    std::vector<double> diff;

    for (size_t i = 0; i < std::max(a.size(), b.size()); ++i)
    {
        diff.emplace_back(a[i] - b[i]);
    }

    return diff;
}

#endif