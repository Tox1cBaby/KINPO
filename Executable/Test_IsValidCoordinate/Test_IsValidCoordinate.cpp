#include "pch.h"
#include "CppUnitTest.h"
#include "../PointInPolygon/PointInPolygon.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IsValidCoordinateTests
{
    TEST_CLASS(IsValidCoordinateTests)
    {
    public:
        TEST_METHOD(ValidMinimumCoordinate)
        {
            bool result = isValidCoordinate(MIN_COORDINATE);
            Assert::IsTrue(result);
        }

        TEST_METHOD(ValidMaximumCoordinate)
        {
            bool result = isValidCoordinate(MAX_COORDINATE);
            Assert::IsTrue(result);
        }

        TEST_METHOD(ValidMiddleCoordinate)
        {
            bool result = isValidCoordinate(0.0);
            Assert::IsTrue(result);
        }

        TEST_METHOD(InvalidLowerCoordinate)
        {
            bool result = isValidCoordinate(MIN_COORDINATE - 0.1);
            Assert::IsFalse(result);
        }

        TEST_METHOD(InvalidHigherCoordinate)
        {
            bool result = isValidCoordinate(MAX_COORDINATE + 0.1);
            Assert::IsFalse(result);
        }

        TEST_METHOD(ValidDecimalCoordinate)
        {
            bool result = isValidCoordinate(123.456);
            Assert::IsTrue(result);
        }

        TEST_METHOD(ValidNegativeCoordinate)
        {
            bool result = isValidCoordinate(-500.5);
            Assert::IsTrue(result);
        }
    };
}