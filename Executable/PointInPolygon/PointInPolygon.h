#ifndef POINT_IN_POLYGON_H
#define POINT_IN_POLYGON_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <limits>

using namespace std;

/**
 * @brief Структура для представления точки на плоскости
 */
struct Point
{
    double x;
    double y;
};

/**
 * @brief Структура для представления многоугольника
 */
struct Polygon
{
    vector<Point> vertices;
};

/**
 * @brief Перечисление типов ошибок
 */
enum error_type
{
    FILE_NOT_FOUND,
    OUTPUT_FILE_ERROR,
    WRONG_ARGS_COUNT,
    VERTEXES_SECTION_NOT_FOUND,
    POINT_SECTION_NOT_FOUND,
    VERTEX_COUNT_TOO_SMALL,
    VERTEX_COUNT_TOO_BIG,
    VERTEX_FORMAT_ERROR,
    POINT_FORMAT_ERROR,
    COORDINATE_OUT_OF_RANGE,
    INCORRECT_VERTICES_ORDER
};

/**
 * @brief Структура для ошибок
 */
struct Error
{
    enum error_type type;
    int line_num;
    int col_num;
    char symbol;
    string str;
};

// Константы
const int MIN_VERTICES = 3;
const int MAX_VERTICES = 100;
const double MIN_COORDINATE = -1000.0;
const double MAX_COORDINATE = 1000.0;
const int MAX_DECIMAL_PLACES = 6;

/**
 * @brief Формирует сообщение об ошибке
 * @param error Объект ошибки
 * @return Строка с сообщением об ошибке
 */
string getErrorMessage(const Error& error);

/**
 * @brief Создает исключение с заданным типом ошибки
 * @param type Тип ошибки
 * @param line Номер строки
 * @param col Номер столбца
 * @param symbol Символ
 * @param str Строка с дополнительной информацией
 */
void throwError(enum error_type type, int line = 0, int col = 0, char symbol = ' ', const string& str = "");

/**
 * @brief Проверка корректности координаты
 * @param coord Координата для проверки
 * @return true если координата находится в допустимом диапазоне, иначе false
 */
bool isValidCoordinate(double coord);

/**
 * @brief Чтение числа с плавающей точкой из строки
 * @param str Исходная строка
 * @param pos Позиция, с которой начинается чтение (обновляется после чтения)
 * @param value Переменная для записи результата
 * @return true если число успешно прочитано, иначе false
 */
bool readDouble(const string& str, size_t& pos, double& value);

/**
 * @brief Чтение данных из входного файла
 * @param filename Имя входного файла
 * @param polygon Многоугольник для заполнения данными
 * @param testPoint Точка для проверки принадлежности
 */
void readInputFile(const string& filename, Polygon& polygon, Point& testPoint);

/**
 * @brief Проверка порядка обхода вершин многоугольника
 * @param polygon Многоугольник для проверки
 * @return true если порядок верен, иначе false
 */
bool checkVerticesOrder(const Polygon& polygon);

/**
 * @brief Проверка принадлежности точки многоугольнику
 * @param polygon Многоугольник
 * @param point Точка для проверки
 * @return true если точка принадлежит многоугольнику, иначе false
 */
bool isPointInPolygon(const Polygon& polygon, const Point& point);

/**
 * @brief Запись результата проверки в выходной файл
 * @param outputFile Имя выходного файла
 * @param testPoint Проверяемая точка
 * @param isInside Результат проверки: true если точка внутри многоугольника, иначе false
 */
void writeResult(const string& outputFile, const Point& testPoint, bool isInside);

#endif