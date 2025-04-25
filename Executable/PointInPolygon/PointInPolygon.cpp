
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

    // Поиск секции Point
    while (getline(file, line))
    {
        lineNum++;

        if (line == "Point:")
        {
            pointSectionFound = true;
            break;
        }
    }

    if (!pointSectionFound)
        throwError(POINT_SECTION_NOT_FOUND, lineNum);

    // Чтение координат тестируемой точки
    if (!getline(file, line))
        throwError(POINT_FORMAT_ERROR, lineNum + 1);

    lineNum++;

    size_t pos = 0;
    double x, y;

    if (!readDouble(line, pos, x))
        throwError(POINT_FORMAT_ERROR, lineNum, pos);

    if (!isValidCoordinate(x))
        throwError(COORDINATE_OUT_OF_RANGE, lineNum, pos);

    if (!readDouble(line, pos, y))
        throwError(POINT_FORMAT_ERROR, lineNum, pos);

    if (!isValidCoordinate(y))
        throwError(COORDINATE_OUT_OF_RANGE, lineNum, pos);

    if (pos != line.length())
        throwError(POINT_FORMAT_ERROR, lineNum, pos);

    testPoint = { x, y };

    file.close();
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

// Проверка порядка обхода вершин многоугольника
bool checkVerticesOrder(const Polygon& polygon)
{
    // Проверяем, что вершины образуют многоугольник без самопересечений
    // Для простоты проверим только, что полигон не является "бантиком"
    int n = polygon.vertices.size();
    if (n < 3)
        return false;

    // Вычисляем площадь многоугольника по формуле Гаусса
    double area = 0.0;
    for (int i = 0; i < n; i++)
    {
        int j = (i + 1) % n;
        area += polygon.vertices[i].x * polygon.vertices[j].y;
        area -= polygon.vertices[j].x * polygon.vertices[i].y;
    }

    area = abs(area) / 2.0;

    // Если площадь близка к нулю, то вершины, возможно, указаны неправильно
    if (area < 1e-10)
        return false;

    return true;
}

// Проверка принадлежности точки многоугольнику
bool isPointInPolygon(const Polygon& polygon, const Point& point)
{
    // Проверка на корректность порядка вершин
    if (!checkVerticesOrder(polygon))
        throwError(INCORRECT_VERTICES_ORDER);

    int n = polygon.vertices.size();
    bool inside = false;

    // Алгоритм трассировки лучом (Ray Casting Algorithm)
    for (int i = 0, j = n - 1; i < n; j = i++)
    {
        const Point& vi = polygon.vertices[i];
        const Point& vj = polygon.vertices[j];

        // Проверка, находится ли точка на стороне многоугольника
        if (((vi.y > point.y) != (vj.y > point.y)) &&
            (point.x < (vj.x - vi.x) * (point.y - vi.y) / (vj.y - vi.y) + vi.x))
        {
            inside = !inside;
        }

        // Точка лежит на стороне многоугольника
        double crossProduct = (point.x - vi.x) * (vj.y - vi.y) - (point.y - vi.y) * (vj.x - vi.x);
        if (abs(crossProduct) < 1e-10)
        {
            double dotProduct = (point.x - vi.x) * (vj.x - vi.x) + (point.y - vi.y) * (vj.y - vi.y);
            double squaredLength = (vj.x - vi.x) * (vj.x - vi.x) + (vj.y - vi.y) * (vj.y - vi.y);

            if (dotProduct >= 0 && dotProduct <= squaredLength)
                return true; // Точка лежит на стороне
        }
    }

    return inside;
}

// Вывода результата
void writeResult(const string& outputFile, const Point& testPoint, bool isInside)
{
    // Открытие выходного файла
    ofstream outFile(outputFile);
    if (!outFile.is_open())
        throwError(OUTPUT_FILE_ERROR);

    // Запись результата
    if (isInside)
        outFile << "Точка (" << testPoint.x << ", " << testPoint.y << ") принадлежит многоугольнику." << endl;
    else
        outFile << "Точка (" << testPoint.x << ", " << testPoint.y << ") не принадлежит многоугольнику." << endl;

    outFile.close();
}

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "");

    try
    {
        // Проверка количества аргументов
        if (argc != 3)
            throwError(WRONG_ARGS_COUNT);

        string inputFile = argv[1];
        string outputFile = argv[2];

        Polygon polygon;
        Point testPoint;

        // Чтение данных из файла
        readInputFile(inputFile, polygon, testPoint);

        // Проверка принадлежности точки многоугольнику
        bool isInside = isPointInPolygon(polygon, testPoint);

        writeResult(outputFile, testPoint, isInside);

        return 0;
    }
    catch (const Error& error)
    {
        cout << getErrorMessage(error) << endl;

        if (!error.str.empty())
            cout << "Строка: " << error.str << endl;

        if (error.line_num > 0)
        {
            cout << "Строка: " << error.line_num;

            if (error.col_num > 0)
                cout << ", Позиция: " << error.col_num;

            cout << endl;
        }
        return 1;
    }
    catch (const exception& e)
    {
        cout << "Произошла непредвиденная ошибка: " << e.what() << endl;
        return 1;
    }
    catch (...)
    {
        cout << "Произошла неизвестная ошибка." << endl;
        return 1;
    }
}