#include "mathlib.hpp"
#include <math.h>
#include <float.h>

MathError math_add(double a, double b, double* result) {
    if (!result) {
        return MATH_ERR_INVALID_ARG;
    }
    
    if ((a > 0. && b > 0. && a > DBL_MAX - b) ||
        (a < 0. && b < 0. && a < -DBL_MAX - b)) {
        return MATH_ERR_OVERFLOW;
    }
    
    *result = a + b;
    return MATH_OK;
}

MathError math_sub(double a, double b, double* result) {
    if (!result) {
        return MATH_ERR_INVALID_ARG;
    }
    
    if ((a > 0. && b < 0. && a > DBL_MAX + b) ||
        (a < 0. && b > 0. && a < -DBL_MAX + b)) {
        return MATH_ERR_OVERFLOW;
    }
    
    *result = a - b;
    return MATH_OK;
}

MathError math_mul(double a, double b, double* result) {
    if (!result) {
        return MATH_ERR_INVALID_ARG;
    }
    
    if (b == 0.) {
        *result = 0.;
        return MATH_OK;
    }
    
    double abs_a = fabs(a);
    double abs_b = fabs(b);
    
    if (abs_a > DBL_MAX / abs_b) {
        return MATH_ERR_OVERFLOW;
    }
    
    *result = a * b;
    return MATH_OK;
}

MathError math_div(double a, double b, double* result) {
    if (!result) {
        return MATH_ERR_INVALID_ARG;
    }
    
    if (b == 0.) {
        return MATH_ERR_DIV_ZERO;
    }
    
    double abs_a = fabs(a);
    double abs_b = fabs(b);
    
    if (abs_b < 1. && abs_a > DBL_MAX * abs_b) {
        return MATH_ERR_OVERFLOW;
    }
    
    *result = a / b;
    return MATH_OK;
}

MathError math_pow(double base, double exp, double* result) {
    if (!result) {
        return MATH_ERR_INVALID_ARG;
    }
    
    if (exp == 0) {
        *result = 1.;
        return MATH_OK;
    }
    
    if (base == 0.) {
        if (exp < 0) {
            return MATH_ERR_DIV_ZERO;
        }
        *result = 0.;
        return MATH_OK;
    }
    
    if (exp == 1) {
        *result = base;
        return MATH_OK;
    }
    
    bool negative_exp = exp < 0;
    double abs_exp = fabs(exp);
    
    *result = 1.;
    
    while (abs_exp > 0) {
        MathError status = math_mul(*result, base, result);
        if (status != MATH_OK) {
            return status;
        }
        abs_exp -= 1.;
    }
    
    if (negative_exp) {
        if (fabs(*result) < 1. / DBL_MAX) {
            return MATH_ERR_OVERFLOW;
        }
        *result = 1. / (*result);
    }
    
    return MATH_OK;
}

MathError math_factorial(double n, double* result) {
    if (!result) {
        return MATH_ERR_INVALID_ARG;
    }
    
    if (n < 0 || floor(n) != n) {
        return MATH_ERR_INVALID_ARG;
    }
    
    // 170! ≈ 7.26e306, 171! > DBL_MAX
    if (n > 170) {
        return MATH_ERR_OVERFLOW;
    }
    
    if (n <= 1.) {
        *result = 1.;
        return MATH_OK;
    }
    
    double sub_result = 1.;
    MathError status = math_factorial(n - 1, &sub_result);

    if (status != MATH_OK) {
        return status;
    }
    
    return math_mul(n, sub_result, result);
}

const char* math_error_string(MathError err) {
    switch (err) {
        case MATH_OK:
            return "Success";
        case MATH_ERR_OVERFLOW:
            return "Overflow detected";
        case MATH_ERR_DIV_ZERO:
            return "Division by zero";
        case MATH_ERR_INVALID_ARG:
            return "Invalid argument";
        default:
            return "Unknown error";
    }
}
