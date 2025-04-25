#include "pch.h"
#include "CppUnitTest.h"
#include "../PointInPolygon/PointInPolygon.h"
#include <fstream>
#include <cstdio>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WriteResultTests
{
    TEST_CLASS(WriteResultTests)
    {
    private:
        // Вспомогательная функция для чтения содержимого файла
        std::string readFileContent(const std::string& filename) {
            std::ifstream file(filename);
            std::string content;
            std::string line;

            while (std::getline(file, line)) {
                content += line + "\n";
            }

            file.close();
            return content;
        }

        void cleanupTempFile(const std::string& filename) {
            std::remove(filename.c_str());
        }

    public:
        TEST_METHOD(WritePointInsideResult)
        {
            std::string filename = "test_output.txt";
            Point point = { 5.5, 7.75 };
            bool isInside = true;

            writeResult(filename, point, isInside);

            std::string content = readFileContent(filename);
            std::string expected = "Точка (5.5, 7.75) принадлежит многоугольнику.\n";

            Assert::AreEqual(expected, content);

            cleanupTempFile(filename);
        }

        TEST_METHOD(WritePointOutsideResult)
        {
            std::string filename = "test_output.txt";
            Point point = { -3.25, 4.125 };
            bool isInside = false;

            writeResult(filename, point, isInside);

            std::string content = readFileContent(filename);
            std::string expected = "Точка (-3.25, 4.125) не принадлежит многоугольнику.\n";

            Assert::AreEqual(expected, content);

            cleanupTempFile(filename);
        }

        TEST_METHOD(WriteIntegerCoordinatesResult)
        {
            std::string filename = "test_output.txt";
            Point point = { 10, 20 };
            bool isInside = true;

            writeResult(filename, point, isInside);

            std::string content = readFileContent(filename);
            std::string expected = "Точка (10, 20) принадлежит многоугольнику.\n";

            Assert::AreEqual(expected, content);

            cleanupTempFile(filename);
        }

        TEST_METHOD(ThrowsOnInvalidOutputFile)
        {
            // Создание несуществующего или недопустимого пути к файлу
            std::string filename = "C:/invalid_directory/test_output.txt";
            Point point = { 5, 5 };
            bool isInside = true;

            try
            {
                writeResult(filename, point, isInside);
                Assert::Fail(L"Exception was not thrown");
            }
            catch (const Error& error)
            {
                Assert::AreEqual((int)OUTPUT_FILE_ERROR, (int)error.type);
            }
            catch (...)
            {
                Assert::Fail(L"Wrong exception type was thrown");
            }
        }
    };
}