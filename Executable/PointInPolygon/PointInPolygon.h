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
 * @brief ��������� ��� ������������� ����� �� ���������
 */
struct Point
{
    double x;
    double y;
};

/**
 * @brief ��������� ��� ������������� ��������������
 */
struct Polygon
{
    vector<Point> vertices;
};

/**
 * @brief ������������ ����� ������
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
 * @brief ��������� ��� ������
 */
struct Error
{
    enum error_type type;
    int line_num;
    int col_num;
    char symbol;
    string str;
};

// ���������
const int MIN_VERTICES = 3;
const int MAX_VERTICES = 100;
const double MIN_COORDINATE = -1000.0;
const double MAX_COORDINATE = 1000.0;
const int MAX_DECIMAL_PLACES = 6;

/**
 * @brief ��������� ��������� �� ������
 * @param error ������ ������
 * @return ������ � ���������� �� ������
 */
string getErrorMessage(const Error& error);

/**
 * @brief ������� ���������� � �������� ����� ������
 * @param type ��� ������
 * @param line ����� ������
 * @param col ����� �������
 * @param symbol ������
 * @param str ������ � �������������� �����������
 */
void throwError(enum error_type type, int line = 0, int col = 0, char symbol = ' ', const string& str = "");

/**
 * @brief �������� ������������ ����������
 * @param coord ���������� ��� ��������
 * @return true ���� ���������� ��������� � ���������� ���������, ����� false
 */
bool isValidCoordinate(double coord);

/**
 * @brief ������ ����� � ��������� ������ �� ������
 * @param str �������� ������
 * @param pos �������, � ������� ���������� ������ (����������� ����� ������)
 * @param value ���������� ��� ������ ����������
 * @return true ���� ����� ������� ���������, ����� false
 */
bool readDouble(const string& str, size_t& pos, double& value);

/**
 * @brief ������ ������ �� �������� �����
 * @param filename ��� �������� �����
 * @param polygon ������������� ��� ���������� �������
 * @param testPoint ����� ��� �������� ��������������
 */
void readInputFile(const string& filename, Polygon& polygon, Point& testPoint);

/**
 * @brief �������� ������� ������ ������ ��������������
 * @param polygon ������������� ��� ��������
 * @return true ���� ������� �����, ����� false
 */
bool checkVerticesOrder(const Polygon& polygon);

/**
 * @brief �������� �������������� ����� ��������������
 * @param polygon �������������
 * @param point ����� ��� ��������
 * @return true ���� ����� ����������� ��������������, ����� false
 */
bool isPointInPolygon(const Polygon& polygon, const Point& point);

/**
 * @brief ������ ���������� �������� � �������� ����
 * @param outputFile ��� ��������� �����
 * @param testPoint ����������� �����
 * @param isInside ��������� ��������: true ���� ����� ������ ��������������, ����� false
 */
void writeResult(const string& outputFile, const Point& testPoint, bool isInside);

#endif