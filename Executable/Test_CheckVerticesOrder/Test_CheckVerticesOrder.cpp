#include "pch.h"
#include "CppUnitTest.h"
#include "../PointInPolygon/PointInPolygon.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CheckVerticesOrderTests
{
    TEST_CLASS(CheckVerticesOrderTests)
    {
    public:
        TEST_METHOD(ValidSquareClockwise)
        {
            Polygon polygon;
            // �������, ������� �� ������� �������
            polygon.vertices = {
                {0, 0},
                {10, 0},
                {10, 10},
                {0, 10}
            };

            bool result = checkVerticesOrder(polygon);
            Assert::IsTrue(result);
        }

        TEST_METHOD(ValidSquareCounterclockwise)
        {
            Polygon polygon;
            // �������, ������� ������ ������� �������
            polygon.vertices = {
                {0, 0},
                {0, 10},
                {10, 10},
                {10, 0}
            };

            bool result = checkVerticesOrder(polygon);
            Assert::IsTrue(result);
        }

        TEST_METHOD(ValidTriangle)
        {
            Polygon polygon;
            // �����������
            polygon.vertices = {
                {0, 0},
                {10, 0},
                {5, 10}
            };

            bool result = checkVerticesOrder(polygon);
            Assert::IsTrue(result);
        }

        TEST_METHOD(ValidPentagon)
        {
            Polygon polygon;
            // ������������
            polygon.vertices = {
                {0, 0},
                {10, 0},
                {15, 10},
                {5, 15},
                {-5, 10}
            };

            bool result = checkVerticesOrder(polygon);
            Assert::IsTrue(result);
        }

        TEST_METHOD(InvalidTooFewVertices)
        {
            Polygon polygon;
            // ������ ��� �������
            polygon.vertices = {
                {0, 0},
                {10, 0}
            };

            bool result = checkVerticesOrder(polygon);
            Assert::IsFalse(result);
        }

        TEST_METHOD(InvalidZeroAreaPolygon)
        {
            Polygon polygon;
            // ������� ����� �� ����� ������, ������� �������������� = 0
            polygon.vertices = {
                {0, 0},
                {5, 0},
                {10, 0}
            };

            bool result = checkVerticesOrder(polygon);
            Assert::IsFalse(result);
        }

        TEST_METHOD(ValidComplexPolygon)
        {
            Polygon polygon;
            // ������� ������������� (�� ��������)
            polygon.vertices = {
                {0, 0},
                {10, 0},
                {10, 10},
                {5, 5},
                {0, 10}
            };

            bool result = checkVerticesOrder(polygon);
            Assert::IsTrue(result);
        }
    };
}