#include "input.h"

#include <limits>
#include <locale>
#include <sstream>

bool ParseInteger(const std::string& text, int& number)
{
    std::istringstream input(text);
    input.imbue(std::locale::classic());

    int parsedNumber = 0;
    char extraCharacter = '\0';

    if (!(input >> parsedNumber))
    {
        return false;
    }

    if (input >> extraCharacter)
    {
        return false;
    }

    number = parsedNumber;
    return true;
}

bool ReadInteger(std::istream& input, std::ostream& output,
    const std::string& prompt, int& number)
{
    std::string text;

    while (true)
    {
        output << prompt;

        if (!std::getline(input, text))
        {
            output << "\nВвод завершён.\n";
            return false;
        }

        if (ParseInteger(text, number))
        {
            return true;
        }

        output << "Ошибка ввода: введите целое число от "
            << std::numeric_limits<int>::min() << " до "
            << std::numeric_limits<int>::max() << ".\n";
    }
}

bool ReadNumbers(std::istream& input, std::ostream& output,
    int& first, int& second)
{
    if (!ReadInteger(input, output, "Введите первое целое число: ", first))
    {
        return false;
    }

    return ReadInteger(input, output, "Введите второе целое число: ", second);
}
