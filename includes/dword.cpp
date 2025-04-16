#include "dword.hpp"
#include <cmath>

real128::real128(const double hi) 
{
    this->hi = hi;
    this->lo = 0.0;
}

real128::real128(const double hi, const double lo)
{
    this->hi = hi;
    this->lo = lo;
}

real128::real128()
{
    this->hi = 0.0;
    this->lo = 0.0;
}

real128::real128(const std::string& num)
{
    
}

real128 real128::two_sum(const double lhs, const double rhs)
{
    // s + t = lhs + rhs
    double s = lhs + rhs; // result term
    
    double lhs_dash = s - rhs;
    double rhs_dash = s - lhs_dash;

    double delta_lhs = lhs - lhs_dash;
    double delta_rhs = rhs - rhs_dash;

    double t = delta_lhs + delta_rhs; // error term

    return real128(s, t);
}

real128 real128::fast_two_sum(const double lhs, const double rhs)
{
    // s + t = lhs + rhs
    double s = lhs + rhs; // result term
    double z = s - lhs;
    double t = rhs - z; // error term

    return real128(s, t);
}

real128 real128::two_diff(const double lhs, const double rhs)
{
    double d = lhs - rhs;

    double lhs_dash = d - lhs;
    double rhs_dash = d - lhs_dash;

    double delta_lhs = lhs - rhs_dash;
    double delta_rhs = rhs + lhs_dash;
    
    double t = delta_lhs - delta_rhs;

    return real128(d, t);
}

real128 real128::fast_two_diff(const double lhs, const double rhs)
{
    double d = lhs - rhs;
    double z = lhs - d;
    double t = z - rhs;

    return real128(d, t);
}

real128 real128::fast_two_prod(const double lhs, const double rhs)
{   
    // hi + lo = lhs * rhs
    double hi = lhs * rhs;
    double lo = std::fma(lhs, rhs, -hi); // using fused multily-add instruction lhs * rhs - hi

    return real128(hi, lo); 
}

real128 operator+ (const real128& lhs, const real128& rhs)
{
    real128 s = real128::two_sum(lhs.hi, rhs.hi);
    real128 t = real128::two_sum(lhs.lo, rhs.lo);
    
    double c = s.lo + t.hi;

    real128 v = real128::fast_two_sum(s.hi, c);

    double w = t.lo + v.lo;

    real128 z = real128::fast_two_sum(v.hi, w);

    return z;
}

real128 operator- (const real128& lhs, const real128& rhs)
{
    real128 d = real128::two_diff(lhs.hi, rhs.hi);
    real128 t = real128::two_diff(lhs.lo, rhs.lo);

    double c = d.lo + t.hi;

    real128 v = real128::fast_two_sum(d.hi, c);

    double w = t.lo + v.lo;
    
    real128 z = real128::fast_two_sum(v.hi, w);

    return z;
}

real128 operator* (const real128& lhs, const real128& rhs)
{   
    // (lhs.hi, lhs.lo) * (rhs.hi, rhs.lo)
    // using fma instruction
    real128 c = real128::fast_two_prod(lhs.hi, rhs.hi);

    double tl0 = lhs.lo * rhs.lo;
    double tl1 = std::fma(lhs.hi, rhs.lo, c.lo);
    double tl2 = std::fma(lhs.lo, rhs.hi, tl1);

    real128 z = real128::fast_two_sum(c.hi, tl2 + tl0);

    return z;
}

real128 operator/ (const real128& lhs, const real128& rhs)
{
    double th = 1 / rhs.hi;

    double rh = std::fma(-rhs.lo, th, 1);
    double rl = -(rhs.lo * th);

    real128 e = real128::fast_two_sum(rh, rl);

    real128 delta = e * th;

    real128 m = delta + th;

    real128 z = lhs * m;

    return z;
}

real128 operator+ (const real128& lhs, const double rhs)
{
    real128 s = real128::two_sum(lhs.hi, rhs);
    
    double v = lhs.lo + s.lo;

    real128 z = real128::fast_two_sum(s.hi, v);
    
    return z;
}

real128 operator/ (const real128& lhs, const double rhs)
{
    double th = lhs.hi / rhs;

    real128 p = real128::fast_two_prod(th, rhs);

    double delta_h = lhs.hi - p.hi;
    double delta_t = delta_h - p.lo;

    double delta = delta_t + lhs.lo;

    double tl = delta / rhs;

    real128 z = real128::fast_two_sum(th, tl);

    return z;
}

real128 operator- (const real128& lhs, const double rhs)
{
    real128 d = real128::two_diff(lhs.hi, rhs);

    double v = lhs.lo + d.lo;

    real128 z = real128::fast_two_sum(d.hi, v);

    return z;
}

real128 operator* (const real128& lhs, const double rhs)
{
    real128 c = real128::fast_two_prod(lhs.hi, rhs);
    
    double cl2 = lhs.lo * rhs;

    real128 t = real128::fast_two_sum(c.hi, cl2);

    double tl2 = t.lo + c.lo;

    real128 z = real128::fast_two_sum(t.hi, tl2);

    return z;
}

real128 real128::operator+= (const real128& rhs)
{
    (*this) = (*this) + rhs;
    return (*this);
}

real128 real128::operator-= (const real128& rhs)
{
    (*this) = (*this) - rhs;
    return (*this);
}

real128 real128::operator*= (const real128& rhs)
{
    (*this) = (*this) * rhs;
    return (*this);
}

real128 real128::operator/= (const real128& rhs)
{
    (*this) = (*this) / rhs;
    return (*this);
}

double real128::eval() const
{
    return this->hi + this->lo;
}