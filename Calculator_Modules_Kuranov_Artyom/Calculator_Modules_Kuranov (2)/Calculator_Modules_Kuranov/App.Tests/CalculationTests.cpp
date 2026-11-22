#include "CppUnitTest.h"
#include "calculation.h"

#include <climits>
#include <stdexcept>
#include <string>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CalculatorTests
{
    TEST_CLASS(CalculationTests)
    {
    public:
        TEST_METHOD(OriginalPositivePair_ReturnsExpectedResults)
        {
            const int first = 5;
            const int second = 2;

            Assert::AreEqual(7LL, Sum(first, second));
            Assert::AreEqual(3LL, Subtract(first, second));
            Assert::AreEqual(10LL, Multiply(first, second));
            Assert::AreEqual(2.5, Divide(first, second), 0.000000000001);
        }

        TEST_METHOD(OriginalNegativePair_ReturnsExpectedResults)
        {
            const int first = -6;
            const int second = 3;

            Assert::AreEqual(-3LL, Sum(first, second));
            Assert::AreEqual(-9LL, Subtract(first, second));
            Assert::AreEqual(-18LL, Multiply(first, second));
            Assert::AreEqual(-2.0, Divide(first, second), 0.000000000001);
        }

        TEST_METHOD(ZeroDividend_ReturnsExpectedResults)
        {
            const int first = 0;
            const int second = 4;

            Assert::AreEqual(4LL, Sum(first, second));
            Assert::AreEqual(-4LL, Subtract(first, second));
            Assert::AreEqual(0LL, Multiply(first, second));
            Assert::AreEqual(0.0, Divide(first, second), 0.000000000001);
        }

        TEST_METHOD(ZeroDivisor_OtherOperationsRemainValid)
        {
            const int first = 8;
            const int second = 0;

            Assert::AreEqual(8LL, Sum(first, second));
            Assert::AreEqual(8LL, Subtract(first, second));
            Assert::AreEqual(0LL, Multiply(first, second));
        }

        TEST_METHOD(Divide_ZeroDivisor_ThrowsInvalidArgument)
        {
            Assert::ExpectException<std::invalid_argument>([]
            {
                Divide(8, 0);
            });
        }

        TEST_METHOD(Divide_ZeroDivisor_ExceptionHasRequiredMessage)
        {
            bool exceptionThrown = false;

            try
            {
                Divide(8, 0);
            }
            catch (const std::invalid_argument& error)
            {
                exceptionThrown = true;
                Assert::IsTrue(std::string(error.what()) == "На ноль делить нельзя");
            }

            Assert::IsTrue(exceptionThrown);
        }

        TEST_METHOD(Sum_IntLimits_ReturnsWidenedResults)
        {
            Assert::AreEqual(4294967294LL, Sum(INT_MAX, INT_MAX));
            Assert::AreEqual(-4294967296LL, Sum(INT_MIN, INT_MIN));
        }

        TEST_METHOD(Subtract_IntLimits_ReturnsWidenedResults)
        {
            Assert::AreEqual(4294967295LL, Subtract(INT_MAX, INT_MIN));
            Assert::AreEqual(-4294967295LL, Subtract(INT_MIN, INT_MAX));
        }

        TEST_METHOD(Multiply_IntLimits_ReturnsWidenedResults)
        {
            Assert::AreEqual(4611686014132420609LL, Multiply(INT_MAX, INT_MAX));
            Assert::AreEqual(4611686018427387904LL, Multiply(INT_MIN, INT_MIN));
            Assert::AreEqual(-4611686016279904256LL, Multiply(INT_MIN, INT_MAX));
        }

        TEST_METHOD(Divide_IntMinByMinusOne_ReturnsPositiveDouble)
        {
            const double result = Divide(INT_MIN, -1);

            Assert::AreEqual(2147483648.0, result, 0.000000000001);
        }

        TEST_METHOD(Divide_OneByThree_PreservesFraction)
        {
            const double result = Divide(1, 3);

            Assert::AreEqual(0.3333333333333333, result, 0.000000000001);
        }
    };
}
