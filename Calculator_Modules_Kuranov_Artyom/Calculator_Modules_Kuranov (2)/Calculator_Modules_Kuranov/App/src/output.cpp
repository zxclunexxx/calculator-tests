#include "output.h"

#include "calculation.h"

#include <iomanip>
#include <locale>
#include <sstream>

void PrintIntroduction(std::ostream& output)
{
    output << "Консольный калькулятор\n"
        << "Введите два целых числа (каждое с новой строки).\n";
}

std::string FormatResults(int first, int second)
{
    std::ostringstream result;
    result.imbue(std::locale::classic());
    result << std::setprecision(15);

    result << "Сумма: " << Sum(first, second) << '\n';
    result << "Разность: " << Subtract(first, second) << '\n';
    result << "Произведение: " << Multiply(first, second) << '\n';

    if (second == 0)
    {
        result << "На ноль делить нельзя\n";
    }
    else
    {
        result << "Частное: " << Divide(first, second) << '\n';
    }

    return result.str();
}

void PrintResults(std::ostream& output, int first, int second)
{
    output << FormatResults(first, second);
}
