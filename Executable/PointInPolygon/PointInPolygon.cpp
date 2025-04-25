
#include <iostream>
#include "PointInPolygon.h"

using namespace std;

// Функции для работы с ошибками
string getErrorMessage(const Error& error)
{
    switch (error.type)
    {
    case FILE_NOT_FOUND:
        return "Файл с входными данными указан некорректно. Файл может не существовать.";
    case OUTPUT_FILE_ERROR:
        return "Выходной файл указан некорректно. Возможно, указанное расположение не существует или отсутствуют права на запись.";
    case WRONG_ARGS_COUNT:
        return "Программа принимает два аргумента: <путь к входному файлу> <путь к выходному файлу>";
    case VERTEXES_SECTION_NOT_FOUND:
        return "Неверная структура входного файла. Раздел Vertexes не найден.";
    case POINT_SECTION_NOT_FOUND:
        return "Неверная структура входного файла. Раздел Point не найден.";
    case VERTEX_COUNT_TOO_SMALL:
        return "Ошибка в разделе Vertexes: количество вершин должно быть не менее 3.";
    case VERTEX_COUNT_TOO_BIG:
        return "Ошибка в разделе Vertexes: количество вершин не должно превышать 100.";
    case VERTEX_FORMAT_ERROR:
        return "Ошибка формата координат вершин.";
    case POINT_FORMAT_ERROR:
        return "Ошибка формата координат точки.";
    case COORDINATE_OUT_OF_RANGE:
        return "Ошибка: значение координаты выходит за допустимый диапазон от -1000 до 1000";
    case INCORRECT_VERTICES_ORDER:
        return "Ошибка: вершины многоугольника должны быть указаны в порядке их обхода (по часовой или против часовой стрелки).";
    default:
        return "Неизвестная ошибка.";
    }
}

void throwError(enum error_type type, int line, int col, char symbol, const string& str)
{
    Error error = { type, line, col, symbol, str };
    throw error;
}

// Проверка корректности координаты
bool isValidCoordinate(double coord)
{
    return coord >= MIN_COORDINATE && coord <= MAX_COORDINATE;
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "");

    // Проверка количества аргументов
    if (argc != 3)
        throwError(WRONG_ARGS_COUNT);

    return 0;
}