#include "calculation.h"

#include <stdexcept>

long long Sum(int first, int second)
{
    return static_cast<long long>(first) + second;
}

long long Subtract(int first, int second)
{
    return static_cast<long long>(first) - second;
}

long long Multiply(int first, int second)
{
    return static_cast<long long>(first) * second;
}

double Divide(int first, int second)
{
    if (second == 0)
    {
        throw std::invalid_argument("На ноль делить нельзя");
    }

    return static_cast<double>(first) / second;
}
