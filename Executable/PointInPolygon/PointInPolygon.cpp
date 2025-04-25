
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

// Чтение данных из файла
void readInputFile(const string& filename, Polygon& polygon, Point& testPoint)
{
    ifstream file(filename);

    if (!file.is_open())
        throwError(FILE_NOT_FOUND);

    string line;
    int lineNum = 0;
    bool vertexesSectionFound = false;
    bool pointSectionFound = false;
    int vertexCount = 0;

    // Поиск секции Vertexes
    while (getline(file, line))
    {
        lineNum++;

        if (line == "Vertexes:")
        {
            vertexesSectionFound = true;
            break;
        }
    }

    if (!vertexesSectionFound)
        throwError(VERTEXES_SECTION_NOT_FOUND, lineNum);

    // Чтение количества вершин
    if (!getline(file, line))
        throwError(VERTEX_COUNT_TOO_SMALL, lineNum + 1);

    lineNum++;

    try
    {
        vertexCount = stoi(line);
    }
    catch (...)
    {
        throwError(VERTEX_FORMAT_ERROR, lineNum, 0);
    }

    if (vertexCount < MIN_VERTICES) throwError(VERTEX_COUNT_TOO_SMALL, lineNum);

    if (vertexCount > MAX_VERTICES) throwError(VERTEX_COUNT_TOO_BIG, lineNum);

    // Чтение координат вершин
    for (int i = 0; i < vertexCount; i++)
    {
        if (!getline(file, line)) throwError(VERTEX_FORMAT_ERROR, lineNum + 1);

        lineNum++;

        size_t pos = 0;
        double x, y;

        if (!readDouble(line, pos, x))
            throwError(VERTEX_FORMAT_ERROR, lineNum, pos);

        if (!isValidCoordinate(x))
            throwError(COORDINATE_OUT_OF_RANGE, lineNum, pos);

        if (!readDouble(line, pos, y))
            throwError(VERTEX_FORMAT_ERROR, lineNum, pos);

        if (!isValidCoordinate(y))
            throwError(COORDINATE_OUT_OF_RANGE, lineNum, pos);

        if (pos != line.length())
            throwError(VERTEX_FORMAT_ERROR, lineNum, pos);

        polygon.vertices.push_back({ x, y });
    }
}

// Чтение числа с плавающей точкой из строки
bool readDouble(const string& str, size_t& pos, double& value)
{
    size_t start = pos;

    // Пропускаем начальные пробелы
    while (pos < str.length() && isspace(str[pos]))
        pos++;

    if (pos >= str.length())
        return false;

    // Проверяем знак числа
    bool negative = false;
    if (str[pos] == '-')
    {
        negative = true;
        pos++;
    }
    else if (str[pos] == '+')
        pos++;

    // Читаем цифры до десятичной точки
    double result = 0.0;
    bool hasDigits = false;

    while (pos < str.length() && isdigit(str[pos]))
    {
        result = result * 10.0 + (str[pos] - '0');
        hasDigits = true;
        pos++;
    }

    // Читаем десятичную дробь
    if (pos < str.length() && str[pos] == '.')
    {
        pos++;

        double fraction = 0.0;
        double scale = 0.1;
        int decimalPlaces = 0;

        while (pos < str.length() && isdigit(str[pos]) && decimalPlaces < MAX_DECIMAL_PLACES)
        {
            fraction += (str[pos] - '0') * scale;
            scale *= 0.1;
            decimalPlaces++;
            pos++;
        }

        // Пропускаем лишние знаки после запятой
        while (pos < str.length() && isdigit(str[pos]))
            pos++;

        result += fraction;
    }

    if (!hasDigits) return false;

    value = negative ? -result : result;

    // Проверяем, что после числа идут только пробелы
    while (pos < str.length() && isspace(str[pos]))
        pos++;

    return true;
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

    string inputFile = argv[1];
    string outputFile = argv[2];

    Polygon polygon;
    Point testPoint;

    // Чтение данных из файла
    readInputFile(inputFile, polygon, testPoint);

    return 0;
}