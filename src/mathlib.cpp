#include "mathlib.h"
#include <math.h>
#include <float.h>
#include <limits.h>

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

MathError math_pow(double base, long long exp, double* result) {
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
    unsigned long long abs_exp = negative_exp ? (unsigned long long)(-exp) : (unsigned long long)exp;
    
    *result = 1.;
    
    while (abs_exp > 0) {
        MathError status = math_mul(*result, base, result);
        if (status != MATH_OK)
            return status;
        --abs_exp;
    }
    
    if (negative_exp) {
        if (fabs(*result) < 1. / DBL_MAX) {
            return MATH_ERR_OVERFLOW;
        }
        
        *result = 1. / (*result);
    }
    
    return MATH_OK;
}

MathError math_factorial(long long n, unsigned long long* result) {
    if (!result || n < 0) {
        return MATH_ERR_INVALID_ARG;
    }
    
    if (n <= 1) {
        *result = 1;
        return MATH_OK;
    }
    
    if (n > 20) {
        return MATH_ERR_OVERFLOW;
    }
    
    unsigned long long sub_result = 0;
    MathError status = math_factorial(n - 1, &sub_result);
    
    if (status != MATH_OK)
        return status;

    if (n > ULLONG_MAX / sub_result) {
        return MATH_ERR_OVERFLOW;
    }

    *result = n * sub_result;
    return MATH_OK;
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
