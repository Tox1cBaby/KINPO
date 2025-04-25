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
            // Квадрат 10x10
            polygon.vertices = {
                {0, 0},
                {10, 0},
                {10, 10},
                {0, 10}
            };

            Point point = { 5, 5 }; // Точка внутри квадрата

            bool result = isPointInPolygon(polygon, point);
            Assert::IsTrue(result);
        }

        TEST_METHOD(PointOutsideSquare)
        {
            Polygon polygon;
            // Квадрат 10x10
            polygon.vertices = {
                {0, 0},
                {10, 0},
                {10, 10},
                {0, 10}
            };

            Point point = { 15, 15 }; // Точка вне квадрата

            bool result = isPointInPolygon(polygon, point);
            Assert::IsFalse(result);
        }

        TEST_METHOD(PointOnSquareVertex)
        {
            Polygon polygon;
            // Квадрат 10x10
            polygon.vertices = {
                {0, 0},
                {10, 0},
                {10, 10},
                {0, 10}
            };

            Point point = { 0, 0 }; // Точка на вершине квадрата

            bool result = isPointInPolygon(polygon, point);
            Assert::IsTrue(result);
        }

        TEST_METHOD(PointOnSquareEdge)
        {
            Polygon polygon;
            // Квадрат 10x10
            polygon.vertices = {
                {0, 0},
                {10, 0},
                {10, 10},
                {0, 10}
            };

            Point point = { 5, 0 }; // Точка на стороне квадрата

            bool result = isPointInPolygon(polygon, point);
            Assert::IsTrue(result);
        }

        TEST_METHOD(PointInsideTriangle)
        {
            Polygon polygon;
            // Треугольник
            polygon.vertices = {
                {0, 0},
                {10, 0},
                {5, 10}
            };

            Point point = { 5, 5 }; // Точка внутри треугольника

            bool result = isPointInPolygon(polygon, point);
            Assert::IsTrue(result);
        }

        TEST_METHOD(PointOutsideTriangle)
        {
            Polygon polygon;
            // Треугольник
            polygon.vertices = {
                {0, 0},
                {10, 0},
                {5, 10}
            };

            Point point = { 7, 8 }; // Точка вне треугольника

            bool result = isPointInPolygon(polygon, point);
            Assert::IsFalse(result);
        }

        TEST_METHOD(PointInsideComplexPolygon)
        {
            Polygon polygon;
            // Сложный многоугольник (не выпуклый)
            polygon.vertices = {
                {0, 0},
                {10, 0},
                {10, 10},
                {5, 5},
                {0, 10}
            };

            Point point = { 3, 3 }; // Точка внутри многоугольника

            bool result = isPointInPolygon(polygon, point);
            Assert::IsTrue(result);
        }

        TEST_METHOD(PointInConcavity)
        {
            Polygon polygon;
            // Сложный многоугольник с вогнутостью
            polygon.vertices = {
                {0, 0},
                {10, 0},
                {10, 10},
                {5, 2}, // Вогнутость
                {0, 10}
            };

            Point point = { 5, 5 }; // Точка в вогнутости (должна быть вне многоугольника)

            bool result = isPointInPolygon(polygon, point);
            Assert::IsFalse(result);
        }

        TEST_METHOD(ThrowsOnIncorrectVerticesOrder)
        {
            Polygon polygon;
            // Вершины образуют полигон с нулевой площадью
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
            // Квадрат 10x10
            polygon.vertices = {
                {0, 0},
                {10, 0},
                {10, 10},
                {0, 10}
            };

            Point point = { 5, 0.0000001 }; // Точка очень близко к стороне

            bool result = isPointInPolygon(polygon, point);
            Assert::IsTrue(result);
        }

        TEST_METHOD(EdgeCaseHorizontalRay)
        {
            Polygon polygon;
            // Квадрат 10x10
            polygon.vertices = {
                {0, 0},
                {10, 0},
                {10, 10},
                {0, 10}
            };

            Point point = { 5, 0 }; // Точка на горизонтальной стороне

            bool result = isPointInPolygon(polygon, point);
            Assert::IsTrue(result);
        }

        TEST_METHOD(EdgeCaseVerticalRay)
        {
            Polygon polygon;
            // Квадрат 10x10
            polygon.vertices = {
                {0, 0},
                {10, 0},
                {10, 10},
                {0, 10}
            };

            Point point = { 0, 5 }; // Точка на вертикальной стороне

            bool result = isPointInPolygon(polygon, point);
            Assert::IsTrue(result);
        }
    };
}