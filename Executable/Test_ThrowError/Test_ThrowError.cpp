#include "pch.h"
#include "CppUnitTest.h"
#include "../PointInPolygon/PointInPolygon.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ThrowErrorTests
{
    TEST_CLASS(ThrowErrorTests)
    {
    public:
        TEST_METHOD(ThrowsWithCorrectType)
        {
            try
            {
                throwError(FILE_NOT_FOUND);
                Assert::Fail(L"Exception was not thrown");
            }
            catch (const Error& error)
            {
                Assert::AreEqual((int)FILE_NOT_FOUND, (int)error.type);
                Assert::AreEqual(0, error.line_num);
                Assert::AreEqual(0, error.col_num);
                Assert::AreEqual(' ', error.symbol);
                Assert::IsTrue(error.str.empty());
            }
            catch (...)
            {
                Assert::Fail(L"Wrong exception type was thrown");
            }
        }

        TEST_METHOD(ThrowsWithLineAndColumn)
        {
            int lineNum = 42;
            int colNum = 10;

            try
            {
                throwError(VERTEX_FORMAT_ERROR, lineNum, colNum);
                Assert::Fail(L"Exception was not thrown");
            }
            catch (const Error& error)
            {
                Assert::AreEqual((int)VERTEX_FORMAT_ERROR, (int)error.type);
                Assert::AreEqual(lineNum, error.line_num);
                Assert::AreEqual(colNum, error.col_num);
                Assert::AreEqual(' ', error.symbol);
                Assert::IsTrue(error.str.empty());
            }
            catch (...)
            {
                Assert::Fail(L"Wrong exception type was thrown");
            }
        }

        TEST_METHOD(ThrowsWithAllParameters)
        {
            int lineNum = 42;
            int colNum = 10;
            char symbol = 'x';
            std::string message = "Test error message";

            try
            {
                throwError(POINT_FORMAT_ERROR, lineNum, colNum, symbol, message);
                Assert::Fail(L"Exception was not thrown");
            }
            catch (const Error& error)
            {
                Assert::AreEqual((int)POINT_FORMAT_ERROR, (int)error.type);
                Assert::AreEqual(lineNum, error.line_num);
                Assert::AreEqual(colNum, error.col_num);
                Assert::AreEqual(symbol, error.symbol);
                Assert::AreEqual(message.c_str(), error.str.c_str());
            }
            catch (...)
            {
                Assert::Fail(L"Wrong exception type was thrown");
            }
        }
    };
}