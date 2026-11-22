#include "CppUnitTest.h"
#include "output.h"

#include <climits>
#include <sstream>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CalculatorTests
{
    TEST_CLASS(OutputTests)
    {
    public:
        TEST_METHOD(PrintIntroduction_PrintsRequiredText)
        {
            std::ostringstream output;

            PrintIntroduction(output);

            const std::string expected =
                "Консольный калькулятор\n"
                "Введите два целых числа (каждое с новой строки).\n";
            Assert::IsTrue(output.str() == expected);
        }

        TEST_METHOD(FormatResults_PositivePair_PrintsAllFourResults)
        {
            const std::string result = FormatResults(5, 2);

            const std::string expected =
                "Сумма: 7\n"
                "Разность: 3\n"
                "Произведение: 10\n"
                "Частное: 2.5\n";
            Assert::IsTrue(result == expected);
        }

        TEST_METHOD(FormatResults_NegativePair_PrintsCorrectSigns)
        {
            const std::string result = FormatResults(-6, 3);

            const std::string expected =
                "Сумма: -3\n"
                "Разность: -9\n"
                "Произведение: -18\n"
                "Частное: -2\n";
            Assert::IsTrue(result == expected);
        }

        TEST_METHOD(FormatResults_ZeroDividend_PrintsZeroQuotient)
        {
            const std::string result = FormatResults(0, 4);

            const std::string expected =
                "Сумма: 4\n"
                "Разность: -4\n"
                "Произведение: 0\n"
                "Частное: 0\n";
            Assert::IsTrue(result == expected);
        }

        TEST_METHOD(FormatResults_ZeroDivisor_PrintsRequiredMessage)
        {
            const std::string result = FormatResults(8, 0);

            const std::string expected =
                "Сумма: 8\n"
                "Разность: 8\n"
                "Произведение: 0\n"
                "На ноль делить нельзя\n";
            Assert::IsTrue(result == expected);
        }

        TEST_METHOD(FormatResults_IntMinAndMinusOne_PrintsWidenedResults)
        {
            const std::string result = FormatResults(INT_MIN, -1);

            const std::string expected =
                "Сумма: -2147483649\n"
                "Разность: -2147483647\n"
                "Произведение: 2147483648\n"
                "Частное: 2147483648\n";
            Assert::IsTrue(result == expected);
        }

        TEST_METHOD(FormatResults_OneByThree_PrintsFifteenSignificantDigits)
        {
            const std::string result = FormatResults(1, 3);

            const std::string expected =
                "Сумма: 4\n"
                "Разность: -2\n"
                "Произведение: 3\n"
                "Частное: 0.333333333333333\n";
            Assert::IsTrue(result == expected);
        }

        TEST_METHOD(PrintResults_WritesAllFourResultsToStream)
        {
            std::ostringstream output;

            PrintResults(output, 5, 2);

            const std::string expected =
                "Сумма: 7\n"
                "Разность: 3\n"
                "Произведение: 10\n"
                "Частное: 2.5\n";
            Assert::IsTrue(output.str() == expected);
        }
    };
}
