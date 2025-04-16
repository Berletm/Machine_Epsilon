#ifndef REAL128
#define REAL128

#include <string>

struct real128
{
private:
    double hi, lo;
public:
    explicit real128(const double hi, const double lo);
    explicit real128(const double hi);
    explicit real128(const std::string& num);
    explicit real128();
private:
    static real128 two_sum(const double lhs, const double rhs);
    static real128 fast_two_sum(const double lhs, const double rhs);

    static real128 two_diff(const double lhs, const double rhs);
    static real128 fast_two_diff(const double lhs, const double rhs);

    static real128 fast_two_prod(const double lhs, const double rhs);
public:
    friend real128 operator+ (const real128& lhs, const double rhs);
    friend real128 operator- (const real128& lhs, const double rhs);
    friend real128 operator* (const real128& lhs, const double rhs);
    friend real128 operator/ (const real128& lhs, const double rhs);

    friend real128 operator+ (const real128& lhs, const real128& rhs);
    friend real128 operator- (const real128& lhs, const real128& rhs);
    friend real128 operator* (const real128& lhs, const real128& rhs);
    friend real128 operator/ (const real128& lhs, const real128& rhs);

    real128 operator+= (const real128& rhs);
    real128 operator-= (const real128& rhs);
    real128 operator*= (const real128& rhs);
    real128 operator/= (const real128& rhs);

    double eval() const;
};


#endif