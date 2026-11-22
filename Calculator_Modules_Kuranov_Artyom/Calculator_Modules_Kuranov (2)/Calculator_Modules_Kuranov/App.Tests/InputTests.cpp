#include "CppUnitTest.h"
#include "input.h"

#include <climits>
#include <sstream>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CalculatorTests
{
    TEST_CLASS(InputTests)
    {
    public:
        TEST_METHOD(ParseInteger_PositiveNegativeAndZero_Accepted)
        {
            int value = 99;

            Assert::IsTrue(ParseInteger("42", value));
            Assert::AreEqual(42, value);
            Assert::IsTrue(ParseInteger("+42", value));
            Assert::AreEqual(42, value);
            Assert::IsTrue(ParseInteger("-6", value));
            Assert::AreEqual(-6, value);
            Assert::IsTrue(ParseInteger("0", value));
            Assert::AreEqual(0, value);
        }

        TEST_METHOD(ParseInteger_SurroundingWhitespace_Accepted)
        {
            int value = 99;

            const bool accepted = ParseInteger(" \t -6 \t ", value);

            Assert::IsTrue(accepted);
            Assert::AreEqual(-6, value);
        }

        TEST_METHOD(ParseInteger_IntLimits_Accepted)
        {
            int value = 99;

            Assert::IsTrue(ParseInteger("-2147483648", value));
            Assert::AreEqual(INT_MIN, value);
            Assert::IsTrue(ParseInteger("2147483647", value));
            Assert::AreEqual(INT_MAX, value);
        }

        TEST_METHOD(ParseInteger_EmptyOrWhitespace_RejectedAndKeepsValue)
        {
            const std::string inputs[] = { "", " \t " };

            for (const std::string& input : inputs)
            {
                int value = 99;

                Assert::IsFalse(ParseInteger(input, value));
                Assert::AreEqual(99, value);
            }
        }

        TEST_METHOD(ParseInteger_Letters_RejectedAndKeepsValue)
        {
            int value = 99;

            const bool accepted = ParseInteger("abc", value);

            Assert::IsFalse(accepted);
            Assert::AreEqual(99, value);
        }

        TEST_METHOD(ParseInteger_Fraction_RejectedAndKeepsValue)
        {
            int value = 99;

            const bool accepted = ParseInteger("2.5", value);

            Assert::IsFalse(accepted);
            Assert::AreEqual(99, value);
        }

        TEST_METHOD(ParseInteger_TrailingTextOrSecondNumber_RejectedAndKeepsValue)
        {
            const std::string inputs[] = { "12abc", "5 2" };

            for (const std::string& input : inputs)
            {
                int value = 99;

                Assert::IsFalse(ParseInteger(input, value));
                Assert::AreEqual(99, value);
            }
        }

        TEST_METHOD(ParseInteger_OutOfIntRange_RejectedAndKeepsValue)
        {
            const std::string inputs[] =
            {
                "2147483648",
                "-2147483649",
                "9999999999999999999999999999999999999999"
            };

            for (const std::string& input : inputs)
            {
                int value = 99;

                Assert::IsFalse(ParseInteger(input, value));
                Assert::AreEqual(99, value);
            }
        }

        TEST_METHOD(ParseInteger_SignWithoutDigits_RejectedAndKeepsValue)
        {
            const std::string inputs[] = { "+", "-" };

            for (const std::string& input : inputs)
            {
                int value = 99;

                Assert::IsFalse(ParseInteger(input, value));
                Assert::AreEqual(99, value);
            }
        }

        TEST_METHOD(ReadInteger_ValidLine_ReturnsValueAndPrompt)
        {
            std::istringstream input("5\n");
            std::ostringstream output;
            int value = 99;

            const bool accepted = ReadInteger(input, output, "Число: ", value);

            Assert::IsTrue(accepted);
            Assert::AreEqual(5, value);
            Assert::IsTrue(output.str() == "Число: ");
        }

        TEST_METHOD(ReadInteger_InvalidThenValidLine_RepeatsPrompt)
        {
            std::istringstream input("abc\n2\n");
            std::ostringstream output;
            int value = 99;

            const bool accepted = ReadInteger(input, output, "Число: ", value);

            const std::string expected =
                "Число: "
                "Ошибка ввода: введите целое число от -2147483648 до 2147483647.\n"
                "Число: ";
            Assert::IsTrue(accepted);
            Assert::AreEqual(2, value);
            Assert::IsTrue(output.str() == expected);
        }

        TEST_METHOD(ReadInteger_EndOfInput_ReturnsFalseAndKeepsValue)
        {
            std::istringstream input("");
            std::ostringstream output;
            int value = 99;

            const bool accepted = ReadInteger(input, output, "Число: ", value);

            Assert::IsFalse(accepted);
            Assert::AreEqual(99, value);
            Assert::IsTrue(output.str() == "Число: \nВвод завершён.\n");
        }

        TEST_METHOD(ReadInteger_InvalidThenEndOfInput_ReturnsFalseAndKeepsValue)
        {
            std::istringstream input("abc\n");
            std::ostringstream output;
            int value = 99;

            const bool accepted = ReadInteger(input, output, "Число: ", value);

            const std::string expected =
                "Число: "
                "Ошибка ввода: введите целое число от -2147483648 до 2147483647.\n"
                "Число: \nВвод завершён.\n";
            Assert::IsFalse(accepted);
            Assert::AreEqual(99, value);
            Assert::IsTrue(output.str() == expected);
        }

        TEST_METHOD(ReadNumbers_TwoLines_ReturnsBothValuesAndPrompts)
        {
            std::istringstream input("5\n2\n");
            std::ostringstream output;
            int first = 99;
            int second = 88;

            const bool accepted = ReadNumbers(input, output, first, second);

            const std::string expected =
                "Введите первое целое число: "
                "Введите второе целое число: ";
            Assert::IsTrue(accepted);
            Assert::AreEqual(5, first);
            Assert::AreEqual(2, second);
            Assert::IsTrue(output.str() == expected);
        }

        TEST_METHOD(ReadNumbers_EndBeforeFirst_ReturnsFalseAndKeepsBothValues)
        {
            std::istringstream input("");
            std::ostringstream output;
            int first = 99;
            int second = 88;

            const bool accepted = ReadNumbers(input, output, first, second);

            Assert::IsFalse(accepted);
            Assert::AreEqual(99, first);
            Assert::AreEqual(88, second);
            Assert::IsTrue(output.str() == "Введите первое целое число: \nВвод завершён.\n");
        }

        TEST_METHOD(ReadNumbers_EndBeforeSecond_ReturnsFalseAndKeepsSecondValue)
        {
            std::istringstream input("5\n");
            std::ostringstream output;
            int first = 99;
            int second = 88;

            const bool accepted = ReadNumbers(input, output, first, second);

            const std::string expected =
                "Введите первое целое число: "
                "Введите второе целое число: \nВвод завершён.\n";
            Assert::IsFalse(accepted);
            Assert::AreEqual(5, first);
            Assert::AreEqual(88, second);
            Assert::IsTrue(output.str() == expected);
        }
    };
}
