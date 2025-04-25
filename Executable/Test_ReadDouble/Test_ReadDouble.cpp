#include "pch.h"
#include "CppUnitTest.h"
#include "../PointInPolygon/PointInPolygon.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ReadDoubleTests
{
    TEST_CLASS(ReadDoubleTests)
    {
    public:
        TEST_METHOD(ReadPositiveInteger)
        {
            std::string input = "123";
            size_t pos = 0;
            double value = 0.0;

            bool result = readDouble(input, pos, value);

            Assert::IsTrue(result);
            Assert::AreEqual(123.0, value);
            Assert::AreEqual(input.length(), pos);
        }

        TEST_METHOD(ReadNegativeInteger)
        {
            std::string input = "-456";
            size_t pos = 0;
            double value = 0.0;

            bool result = readDouble(input, pos, value);

            Assert::IsTrue(result);
            Assert::AreEqual(-456.0, value);
            Assert::AreEqual(input.length(), pos);
        }

        TEST_METHOD(ReadPositiveDecimal)
        {
            std::string input = "123.456";
            size_t pos = 0;
            double value = 0.0;

            bool result = readDouble(input, pos, value);

            Assert::IsTrue(result);
            Assert::AreEqual(123.456, value, 0.000001);
            Assert::AreEqual(input.length(), pos);
        }

        TEST_METHOD(ReadNegativeDecimal)
        {
            std::string input = "-789.012";
            size_t pos = 0;
            double value = 0.0;

            bool result = readDouble(input, pos, value);

            Assert::IsTrue(result);
            Assert::AreEqual(-789.012, value, 0.000001);
            Assert::AreEqual(input.length(), pos);
        }

        TEST_METHOD(ReadWithLeadingWhitespace)
        {
            std::string input = "  \t  42.5";
            size_t pos = 0;
            double value = 0.0;

            bool result = readDouble(input, pos, value);

            Assert::IsTrue(result);
            Assert::AreEqual(42.5, value);
            Assert::AreEqual(input.length(), pos);
        }

        TEST_METHOD(ReadWithTrailingWhitespace)
        {
            std::string input = "42.5  \t  ";
            size_t pos = 0;
            double value = 0.0;

            bool result = readDouble(input, pos, value);

            Assert::IsTrue(result);
            Assert::AreEqual(42.5, value);
            Assert::AreEqual(input.length(), pos);
        }

        TEST_METHOD(ReadWithBothWhitespace)
        {
            std::string input = "  \t  42.5  \t  ";
            size_t pos = 0;
            double value = 0.0;

            bool result = readDouble(input, pos, value);

            Assert::IsTrue(result);
            Assert::AreEqual(42.5, value);
            Assert::AreEqual(input.length(), pos);
        }

        TEST_METHOD(ReadWithPositiveSign)
        {
            std::string input = "+42.5";
            size_t pos = 0;
            double value = 0.0;

            bool result = readDouble(input, pos, value);

            Assert::IsTrue(result);
            Assert::AreEqual(42.5, value);
            Assert::AreEqual(input.length(), pos);
        }

        TEST_METHOD(ReadFromMiddleOfString)
        {
            std::string input = "x=42.5 y=10.0";
            size_t pos = 2; // Starting after "x="
            double value = 0.0;

            bool result = readDouble(input, pos, value);

            Assert::IsTrue(result);
            Assert::AreEqual(42.5, value);
            Assert::AreEqual((size_t)7, pos); // Stops after consuming "42.5"
        }

        TEST_METHOD(ReadWithMaxDecimalPlaces)
        {
            std::string input = "42.123456789";
            size_t pos = 0;
            double value = 0.0;

            bool result = readDouble(input, pos, value);

            Assert::IsTrue(result);
            // Should only read MAX_DECIMAL_PLACES (6) after the decimal point
            Assert::AreEqual(42.123456, value, 0.0000001);
            Assert::AreEqual(input.length(), pos); // Should still consume the entire input
        }

        TEST_METHOD(FailOnEmptyString)
        {
            std::string input = "";
            size_t pos = 0;
            double value = 0.0;

            bool result = readDouble(input, pos, value);

            Assert::IsFalse(result);
            Assert::AreEqual(0.0, value);
        }

        TEST_METHOD(FailOnWhitespaceOnly)
        {
            std::string input = "   \t   ";
            size_t pos = 0;
            double value = 0.0;

            bool result = readDouble(input, pos, value);

            Assert::IsFalse(result);
            Assert::AreEqual(0.0, value);
        }

        TEST_METHOD(FailOnNonNumeric)
        {
            std::string input = "abc";
            size_t pos = 0;
            double value = 0.0;

            bool result = readDouble(input, pos, value);

            Assert::IsFalse(result);
            Assert::AreEqual(0.0, value);
        }

        TEST_METHOD(FailOnDecimalPointOnly)
        {
            std::string input = ".";
            size_t pos = 0;
            double value = 0.0;

            bool result = readDouble(input, pos, value);

            Assert::IsFalse(result);
            Assert::AreEqual(0.0, value);
        }

        TEST_METHOD(FailOnSignOnly)
        {
            std::string input = "-";
            size_t pos = 0;
            double value = 0.0;

            bool result = readDouble(input, pos, value);

            Assert::IsFalse(result);
            Assert::AreEqual(0.0, value);
        }
    };
}