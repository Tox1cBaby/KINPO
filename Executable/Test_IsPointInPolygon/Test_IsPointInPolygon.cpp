#include "pch.h"
#include "CppUnitTest.h"
#include "../PointInPolygon/PointInPolygon.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace IsPointInPolygonTests
{
    TEST_CLASS(IsPointInPolygonTests)
    {
    public:
        TEST_METHOD(PointInsideSquare)
        {
            Polygon polygon;
            // ������� 10x10
            polygon.vertices = {
                {0, 0},
                {10, 0},
                {10, 10},
                {0, 10}
            };

            Point point = { 5, 5 }; // ����� ������ ��������

            bool result = isPointInPolygon(polygon, point);
            Assert::IsTrue(result);
        }

        TEST_METHOD(PointOutsideSquare)
        {
            Polygon polygon;
            // ������� 10x10
            polygon.vertices = {
                {0, 0},
                {10, 0},
                {10, 10},
                {0, 10}
            };

            Point point = { 15, 15 }; // ����� ��� ��������

            bool result = isPointInPolygon(polygon, point);
            Assert::IsFalse(result);
        }

        TEST_METHOD(PointOnSquareVertex)
        {
            Polygon polygon;
            // ������� 10x10
            polygon.vertices = {
                {0, 0},
                {10, 0},
                {10, 10},
                {0, 10}
            };

            Point point = { 0, 0 }; // ����� �� ������� ��������

            bool result = isPointInPolygon(polygon, point);
            Assert::IsTrue(result);
        }

        TEST_METHOD(PointOnSquareEdge)
        {
            Polygon polygon;
            // ������� 10x10
            polygon.vertices = {
                {0, 0},
                {10, 0},
                {10, 10},
                {0, 10}
            };

            Point point = { 5, 0 }; // ����� �� ������� ��������

            bool result = isPointInPolygon(polygon, point);
            Assert::IsTrue(result);
        }

        TEST_METHOD(PointInsideTriangle)
        {
            Polygon polygon;
            // �����������
            polygon.vertices = {
                {0, 0},
                {10, 0},
                {5, 10}
            };

            Point point = { 5, 5 }; // ����� ������ ������������

            bool result = isPointInPolygon(polygon, point);
            Assert::IsTrue(result);
        }

        TEST_METHOD(PointOutsideTriangle)
        {
            Polygon polygon;
            // �����������
            polygon.vertices = {
                {0, 0},
                {10, 0},
                {5, 10}
            };

            Point point = { 7, 8 }; // ����� ��� ������������

            bool result = isPointInPolygon(polygon, point);
            Assert::IsFalse(result);
        }

        TEST_METHOD(PointInsideComplexPolygon)
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

            Point point = { 3, 3 }; // ����� ������ ��������������

            bool result = isPointInPolygon(polygon, point);
            Assert::IsTrue(result);
        }

        TEST_METHOD(PointInConcavity)
        {
            Polygon polygon;
            // ������� ������������� � �����������
            polygon.vertices = {
                {0, 0},
                {10, 0},
                {10, 10},
                {5, 2}, // ����������
                {0, 10}
            };

            Point point = { 5, 5 }; // ����� � ���������� (������ ���� ��� ��������������)

            bool result = isPointInPolygon(polygon, point);
            Assert::IsFalse(result);
        }

        TEST_METHOD(ThrowsOnIncorrectVerticesOrder)
        {
            Polygon polygon;
            // ������� �������� ������� � ������� ��������
            polygon.vertices = {
                {0, 0},
                {10, 0},
                {20, 0}
            };

            Point point = { 5, 0 };

            try
            {
                isPointInPolygon(polygon, point);
                Assert::Fail(L"Exception was not thrown");
            }
            catch (const Error& error)
            {
                Assert::AreEqual((int)INCORRECT_VERTICES_ORDER, (int)error.type);
            }
            catch (...)
            {
                Assert::Fail(L"Wrong exception type was thrown");
            }
        }

        TEST_METHOD(EdgeCaseAlmostOnEdge)
        {
            Polygon polygon;
            // ������� 10x10
            polygon.vertices = {
                {0, 0},
                {10, 0},
                {10, 10},
                {0, 10}
            };

            Point point = { 5, 0.0000001 }; // ����� ����� ������ � �������

            bool result = isPointInPolygon(polygon, point);
            Assert::IsTrue(result);
        }

        TEST_METHOD(EdgeCaseHorizontalRay)
        {
            Polygon polygon;
            // ������� 10x10
            polygon.vertices = {
                {0, 0},
                {10, 0},
                {10, 10},
                {0, 10}
            };

            Point point = { 5, 0 }; // ����� �� �������������� �������

            bool result = isPointInPolygon(polygon, point);
            Assert::IsTrue(result);
        }

        TEST_METHOD(EdgeCaseVerticalRay)
        {
            Polygon polygon;
            // ������� 10x10
            polygon.vertices = {
                {0, 0},
                {10, 0},
                {10, 10},
                {0, 10}
            };

            Point point = { 0, 5 }; // ����� �� ������������ �������

            bool result = isPointInPolygon(polygon, point);
            Assert::IsTrue(result);
        }
    };
}