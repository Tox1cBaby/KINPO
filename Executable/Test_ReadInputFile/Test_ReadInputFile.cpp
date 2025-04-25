#include "pch.h"
#include "CppUnitTest.h"
#include "../PointInPolygon/PointInPolygon.h"
#include <fstream>
#include <cstdio>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ReadInputFileTests
{
    TEST_CLASS(ReadInputFileTests)
    {
    private:
        // Вспомогательная функция для создания временного файла
        std::string createTempFileWithContent(const std::string& content) {
            std::string filename = "test_temp_file.txt";
            std::ofstream file(filename);
            file << content;
            file.close();
            return filename;
        }

        void cleanupTempFile(const std::string& filename) {
            std::remove(filename.c_str());
        }

    public:
        TEST_METHOD(ValidInputFileFormat)
        {
            std::string fileContent =
                "Vertexes:\n"
                "4\n"
                "0 0\n"
                "10 0\n"
                "10 10\n"
                "0 10\n"
                "Point:\n"
                "5 5\n";

            std::string filename = createTempFileWithContent(fileContent);

            Polygon polygon;
            Point point;

            readInputFile(filename, polygon, point);

            // Проверка количества вершин
            Assert::AreEqual((size_t)4, polygon.vertices.size());

            // Проверка координат вершин
            Assert::AreEqual(0.0, polygon.vertices[0].x);
            Assert::AreEqual(0.0, polygon.vertices[0].y);

            Assert::AreEqual(10.0, polygon.vertices[1].x);
            Assert::AreEqual(0.0, polygon.vertices[1].y);

            Assert::AreEqual(10.0, polygon.vertices[2].x);
            Assert::AreEqual(10.0, polygon.vertices[2].y);

            Assert::AreEqual(0.0, polygon.vertices[3].x);
            Assert::AreEqual(10.0, polygon.vertices[3].y);

            // Проверка координат точки
            Assert::AreEqual(5.0, point.x);
            Assert::AreEqual(5.0, point.y);

            cleanupTempFile(filename);
        }

        TEST_METHOD(ThrowsOnFileNotFound)
        {
            try
            {
                Polygon polygon;
                Point point;
                readInputFile("non_existent_file.txt", polygon, point);
                Assert::Fail(L"Exception was not thrown");
            }
            catch (const Error& error)
            {
                Assert::AreEqual((int)FILE_NOT_FOUND, (int)error.type);
            }
            catch (...)
            {
                Assert::Fail(L"Wrong exception type was thrown");
            }
        }

        TEST_METHOD(ThrowsOnMissingVertexesSection)
        {
            std::string fileContent =
                "NoVertexes:\n"
                "4\n"
                "0 0\n"
                "10 0\n"
                "10 10\n"
                "0 10\n"
                "Point:\n"
                "5 5\n";

            std::string filename = createTempFileWithContent(fileContent);

            try
            {
                Polygon polygon;
                Point point;
                readInputFile(filename, polygon, point);
                Assert::Fail(L"Exception was not thrown");
            }
            catch (const Error& error)
            {
                Assert::AreEqual((int)VERTEXES_SECTION_NOT_FOUND, (int)error.type);
            }
            catch (...)
            {
                Assert::Fail(L"Wrong exception type was thrown");
            }

            cleanupTempFile(filename);
        }

        TEST_METHOD(ThrowsOnMissingPointSection)
        {
            std::string fileContent =
                "Vertexes:\n"
                "4\n"
                "0 0\n"
                "10 0\n"
                "10 10\n"
                "0 10\n"
                "NoPoint:\n"
                "5 5\n";

            std::string filename = createTempFileWithContent(fileContent);

            try
            {
                Polygon polygon;
                Point point;
                readInputFile(filename, polygon, point);
                Assert::Fail(L"Exception was not thrown");
            }
            catch (const Error& error)
            {
                Assert::AreEqual((int)POINT_SECTION_NOT_FOUND, (int)error.type);
            }
            catch (...)
            {
                Assert::Fail(L"Wrong exception type was thrown");
            }

            cleanupTempFile(filename);
        }

        TEST_METHOD(ThrowsOnTooFewVertices)
        {
            std::string fileContent =
                "Vertexes:\n"
                "2\n"
                "0 0\n"
                "10 0\n"
                "Point:\n"
                "5 5\n";

            std::string filename = createTempFileWithContent(fileContent);

            try
            {
                Polygon polygon;
                Point point;
                readInputFile(filename, polygon, point);
                Assert::Fail(L"Exception was not thrown");
            }
            catch (const Error& error)
            {
                Assert::AreEqual((int)VERTEX_COUNT_TOO_SMALL, (int)error.type);
            }
            catch (...)
            {
                Assert::Fail(L"Wrong exception type was thrown");
            }

            cleanupTempFile(filename);
        }

        TEST_METHOD(ThrowsOnTooManyVertices)
        {
            std::string fileContent = "Vertexes:\n101\n";

            std::string filename = createTempFileWithContent(fileContent);

            try
            {
                Polygon polygon;
                Point point;
                readInputFile(filename, polygon, point);
                Assert::Fail(L"Exception was not thrown");
            }
            catch (const Error& error)
            {
                Assert::AreEqual((int)VERTEX_COUNT_TOO_BIG, (int)error.type);
            }
            catch (...)
            {
                Assert::Fail(L"Wrong exception type was thrown");
            }

            cleanupTempFile(filename);
        }

        TEST_METHOD(ThrowsOnInvalidVertexFormat)
        {
            std::string fileContent =
                "Vertexes:\n"
                "4\n"
                "0 0\n"
                "abc 0\n"  // Некорректный формат
                "10 10\n"
                "0 10\n"
                "Point:\n"
                "5 5\n";

            std::string filename = createTempFileWithContent(fileContent);

            try
            {
                Polygon polygon;
                Point point;
                readInputFile(filename, polygon, point);
                Assert::Fail(L"Exception was not thrown");
            }
            catch (const Error& error)
            {
                Assert::AreEqual((int)VERTEX_FORMAT_ERROR, (int)error.type);
            }
            catch (...)
            {
                Assert::Fail(L"Wrong exception type was thrown");
            }

            cleanupTempFile(filename);
        }

        TEST_METHOD(ThrowsOnInvalidPointFormat)
        {
            std::string fileContent =
                "Vertexes:\n"
                "4\n"
                "0 0\n"
                "10 0\n"
                "10 10\n"
                "0 10\n"
                "Point:\n"
                "abc 5\n";  // Некорректный формат

            std::string filename = createTempFileWithContent(fileContent);

            try
            {
                Polygon polygon;
                Point point;
                readInputFile(filename, polygon, point);
                Assert::Fail(L"Exception was not thrown");
            }
            catch (const Error& error)
            {
                Assert::AreEqual((int)POINT_FORMAT_ERROR, (int)error.type);
            }
            catch (...)
            {
                Assert::Fail(L"Wrong exception type was thrown");
            }

            cleanupTempFile(filename);
        }

        TEST_METHOD(ThrowsOnOutOfRangeCoordinate)
        {
            std::string fileContent =
                "Vertexes:\n"
                "4\n"
                "0 0\n"
                "10 0\n"
                "10 10\n"
                "0 10\n"
                "Point:\n"
                "5 2000\n";  // Координата вне диапазона

            std::string filename = createTempFileWithContent(fileContent);

            try
            {
                Polygon polygon;
                Point point;
                readInputFile(filename, polygon, point);
                Assert::Fail(L"Exception was not thrown");
            }
            catch (const Error& error)
            {
                Assert::AreEqual((int)COORDINATE_OUT_OF_RANGE, (int)error.type);
            }
            catch (...)
            {
                Assert::Fail(L"Wrong exception type was thrown");
            }

            cleanupTempFile(filename);
        }
    };
}