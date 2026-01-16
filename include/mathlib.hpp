#pragma once

typedef enum {
    MATH_OK = 0,
    MATH_ERR_OVERFLOW,
    MATH_ERR_DIV_ZERO,
    MATH_ERR_INVALID_ARG
} MathError;

MathError math_add(double a, double b, double* result);
MathError math_sub(double a, double b, double* result);
MathError math_mul(double a, double b, double* result);
MathError math_div(double a, double b, double* result);
MathError math_pow(double base, double exp, double* result);
MathError math_factorial(double n, double* result);

const char* math_error_string(MathError err);
