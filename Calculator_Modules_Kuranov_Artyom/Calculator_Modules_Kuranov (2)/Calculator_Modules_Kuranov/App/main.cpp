#include <iostream>

#include "input.h"
#include "output.h"

#ifdef _WIN32
#include <Windows.h>
#endif

int main()
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif

    int first = 0;
    int second = 0;

    PrintIntroduction(std::cout);

    if (!ReadNumbers(std::cin, std::cout, first, second))
    {
        return 1;
    }

    PrintResults(std::cout, first, second);
    return 0;
}
