#include "pch.h"
#include "CppUnitTest.h"
#include "../PointInPolygon/PointInPolygon.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace GetErrorMessageTests
{
    TEST_CLASS(GetErrorMessageTests)
    {
    public:
        TEST_METHOD(FileNotFoundError)
        {
            Error error = { FILE_NOT_FOUND, 0, 0, ' ', "" };
            std::string message = getErrorMessage(error);
            Assert::AreEqual("Файл с входными данными указан некорректно. Файл может не существовать.", message.c_str());
        }

        TEST_METHOD(OutputFileError)
        {
            Error error = { OUTPUT_FILE_ERROR, 0, 0, ' ', "" };
            std::string message = getErrorMessage(error);
            Assert::AreEqual("Выходной файл указан некорректно. Возможно, указанное расположение не существует или отсутствуют права на запись.", message.c_str());
        }

        TEST_METHOD(WrongArgsCountError)
        {
            Error error = { WRONG_ARGS_COUNT, 0, 0, ' ', "" };
            std::string message = getErrorMessage(error);
            Assert::AreEqual("Программа принимает два аргумента: <путь к входному файлу> <путь к выходному файлу>", message.c_str());
        }

        TEST_METHOD(VertexesSectionNotFoundError)
        {
            Error error = { VERTEXES_SECTION_NOT_FOUND, 0, 0, ' ', "" };
            std::string message = getErrorMessage(error);
            Assert::AreEqual("Неверная структура входного файла. Раздел Vertexes не найден.", message.c_str());
        }

        TEST_METHOD(PointSectionNotFoundError)
        {
            Error error = { POINT_SECTION_NOT_FOUND, 0, 0, ' ', "" };
            std::string message = getErrorMessage(error);
            Assert::AreEqual("Неверная структура входного файла. Раздел Point не найден.", message.c_str());
        }

        TEST_METHOD(VertexCountTooSmallError)
        {
            Error error = { VERTEX_COUNT_TOO_SMALL, 0, 0, ' ', "" };
            std::string message = getErrorMessage(error);
            Assert::AreEqual("Ошибка в разделе Vertexes: количество вершин должно быть не менее 3.", message.c_str());
        }

        TEST_METHOD(VertexCountTooBigError)
        {
            Error error = { VERTEX_COUNT_TOO_BIG, 0, 0, ' ', "" };
            std::string message = getErrorMessage(error);
            Assert::AreEqual("Ошибка в разделе Vertexes: количество вершин не должно превышать 100.", message.c_str());
        }

        TEST_METHOD(VertexFormatError)
        {
            Error error = { VERTEX_FORMAT_ERROR, 0, 0, ' ', "" };
            std::string message = getErrorMessage(error);
            Assert::AreEqual("Ошибка формата координат вершин.", message.c_str());
        }

        TEST_METHOD(PointFormatError)
        {
            Error error = { POINT_FORMAT_ERROR, 0, 0, ' ', "" };
            std::string message = getErrorMessage(error);
            Assert::AreEqual("Ошибка формата координат точки.", message.c_str());
        }

        TEST_METHOD(CoordinateOutOfRangeError)
        {
            Error error = { COORDINATE_OUT_OF_RANGE, 0, 0, ' ', "" };
            std::string message = getErrorMessage(error);
            Assert::AreEqual("Ошибка: значение координаты выходит за допустимый диапазон от -1000 до 1000", message.c_str());
        }

        TEST_METHOD(IncorrectVerticesOrderError)
        {
            Error error = { INCORRECT_VERTICES_ORDER, 0, 0, ' ', "" };
            std::string message = getErrorMessage(error);
            Assert::AreEqual("Ошибка: вершины многоугольника должны быть указаны в порядке их обхода (по часовой или против часовой стрелки).", message.c_str());
        }

        TEST_METHOD(UnknownError)
        {
            Error error = { (error_type)999, 0, 0, ' ', "" }; // Неизвестный тип ошибки
            std::string message = getErrorMessage(error);
            Assert::AreEqual("Неизвестная ошибка.", message.c_str());
        }
    };
}