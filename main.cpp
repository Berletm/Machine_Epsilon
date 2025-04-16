#include <iostream>
#include "includes/dword.hpp"
#include "includes/funcs.hpp"

#define WITHOUT_NUMPY
#include "includes/matplotlibcpp.h"
namespace plt = matplotlibcpp;

int main()
{
    auto real32_points = generate_arcsin_points<float, float, 150>(50);
    auto real64_points = generate_arcsin_points<double, double, 150>(50);
    auto real128_points = generate_arcsin_points<real128, double, 150>(50);

    auto real32_reference = generate_reference_points<float>(50); 
    auto real64_reference =  generate_reference_points<double>(50); 

    auto x_real32_reference = real32_reference.first, y_real32_reference = real32_reference.second;
    auto x_real64_reference = real64_reference.first, y_real64_reference = real64_reference.second;
    
    auto x_real32 = real32_points.first, y_real32 = real32_points.second;
    auto x_real64 = real64_points.first, y_real64 = real64_points.second;
    auto x_real128 = real128_points.first, y_real128 = real128_points.second;

    auto y_real32_abs_error = calculate_absolute_error<float>(y_real32, y_real32_reference);
    auto y_real64_abs_error = calculate_absolute_error<double>(y_real64, y_real64_reference);
    auto y_real128_abs_error = calculate_absolute_error<double>(y_real128, y_real64_reference);

    auto y_real32_rel_error = calculate_relative_error<float>(y_real32, y_real32_reference);
    auto y_real64_rel_error = calculate_relative_error<double>(y_real64, y_real64_reference);
    auto y_real128_rel_error = calculate_relative_error<double>(y_real128, y_real64_reference);

    auto y_real128_64_diff = calculate_diff(y_real128, y_real64);

    plt::figure(1);
    
    plt::named_loglog("float32", x_real32, y_real32_abs_error);
    plt::named_loglog("float64", x_real64, y_real64_abs_error);
    plt::named_loglog("float128", x_real128, y_real128_abs_error);

    plt::legend();
    plt::title("Arcsin function: log absolute error");
    plt::xlabel("x");
    plt::ylabel("log absolute error arcsin(x)");
    plt::grid(true);

    plt::figure(2);
    plt::plot(y_real32_rel_error, {{"label", "float (32-bit)"}, {"color", "blue"}});
    plt::plot(y_real64_rel_error, {{"label", "double (64-bit)"}, {"color", "green"}});
    plt::plot(y_real128_rel_error, {{"label", "real128 (128-bit)"}, {"color", "red"}});
    plt::legend();
    plt::title("Arcsin function: relative error");
    plt::xlabel("x");
    plt::ylabel("relative error arcsin(x)");
    plt::grid(true);

    plt::figure(3);
    plt::plot(x_real32, y_real32, {{"label", "float (32-bit)"}, {"color", "blue"}});
    plt::plot(x_real64, y_real64, {{"label", "double (64-bit)"}, {"color", "green"}});
    plt::plot(x_real128, y_real128, {{"label", "real128 (128-bit)"}, {"color", "red"}});
    plt::legend();
    plt::title("Arcsin function: relative error");
    plt::xlabel("x");
    plt::ylabel("relative error arcsin(x)");
    plt::grid(true);

    plt::figure(4);
    plt::plot(y_real128_64_diff, {{"label", "float128 - float64"}});
    plt::legend();
    plt::title("Arcsin function: float128 - float64");
    plt::xlabel("x");
    plt::ylabel("y128 - y64");
    plt::grid(true);

    plt::figure(5);
    
    plt::plot(x_real32, y_real32_abs_error, {{"label", "float (32-bit)"}});
    plt::plot(x_real64, y_real64_abs_error,  {{"label", "float (64-bit)"}});
    plt::plot(x_real128, y_real128_abs_error,  {{"label", "float (128-bit)"}});

    plt::legend();
    plt::title("Arcsin function: absolute error");
    plt::xlabel("x");
    plt::ylabel("absolute error arcsin(x)");
    plt::grid(true);

    plt::show();
    
    return 0;
}