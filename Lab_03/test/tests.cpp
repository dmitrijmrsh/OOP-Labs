#include <gtest/gtest.h>
#include "../headers/Point.hpp"
#include "../headers/Figure.hpp"
#include "../headers/Triangle.hpp"
#include "../headers/Square.hpp"
#include "../headers/Octagon.hpp"

TEST(Point_class, default_constructor) {
    Point p;
    ASSERT_TRUE(p.get_x_value() == 0 && p.get_y_value() == 0);
}

TEST(Point_class, values_constructor) {
    Point p(3.2, 1);
    ASSERT_TRUE(p.get_x_value() == 3.2 && p.get_y_value() == 1);
}

TEST(Point_class, copy_constructor) {
    Point a(4.4, 3.545);
    Point b(a);
    ASSERT_TRUE(b.get_x_value() == 4.4 && b.get_y_value() == 3.545);
}

TEST(Point_class, equality_operator_1) {
    Point a(4.4, 3.545);
    Point b(a);
    ASSERT_TRUE(a == b);
}

TEST(Point_class, equality_operator_2) {
    Point a(2, 5);
    Point b(3.4, 2);
    ASSERT_FALSE(a == b);
}

TEST(Point_class, lvalue_copy) {
    Point a(3.45, 2);
    Point b = a;
    ASSERT_TRUE(b.get_x_value() == 3.45 && b.get_y_value() == 2);
}

TEST(Point_class, rvalue_copy) {
    Point a(3.45, 2);
    Point b;
    b = std::move(a);
    ASSERT_TRUE(b.get_x_value() == 3.45 && b.get_y_value() == 2 && a.get_x_value() == 0 && a.get_y_value() == 0);
}

TEST(Point_class, distance_1) {
    Point a(0,3);
    Point b(4,0);
    ASSERT_TRUE(Point::Distance(a, b) == 5);
}

TEST(Point_class, distance_2) {
    Point a(1,1);
    Point b(1,1);
    ASSERT_TRUE(Point::Distance(a, b) == 0);
}

TEST(Triangle_class, default_constructor) {
    Triangle t;
    ASSERT_TRUE(t.getname() == "Triangle");
}

TEST(Triangle_class, points_constructor_1) {
    ASSERT_ANY_THROW(Triangle t(Point(0, 0), Point(0,3), Point(0, 4)));
}

TEST(Triangle_class, points_constructor_2) {
    ASSERT_ANY_THROW(Triangle t(Point(0,0), Point(0, 0), Point(0, 4)));
}

TEST(Triangle_class, copy_constructor) {
    const Point a(0, 0);
    const Point b(1, sqrt(3));
    const Point c(-1, sqrt(3));
    Triangle t(a, b, c);
    Triangle New(t);
    ASSERT_TRUE(New == t);
}

TEST(Triangle_class, destructor_and_points_constructor) {
    Triangle t(Point(1,sqrt(3)), Point(-1,sqrt(3)), Point(0,2*sqrt(3)));
    t.~Triangle();
}

TEST(Triangle_methods, center_method_1) {
    Triangle t(Point(1,sqrt(3)), Point(-1,sqrt(3)), Point(0,2*sqrt(3)));
    Point center = t.Center();
    ASSERT_TRUE(round(center.get_x_value()* 1000) / 1000 == 0 && round(center.get_y_value() * 1000) / 1000 == 2.309);
}

TEST(Triangle_methods, center_method_2) {
    Triangle t(Point(0,0), Point(1,sqrt(3)), Point(-1,sqrt(3)));
    Point center = t.Center();
    ASSERT_TRUE(round(center.get_x_value()* 1000) / 1000 == 0 && round(center.get_y_value() * 1000) / 1000 == 1.155);
}

TEST(Triangle_methods, area_method_1) {
    Triangle t(Point(0,0), Point(1,sqrt(3)), Point(-1,sqrt(3)));
    double area = round(t.Area()*1000)/1000;
    ASSERT_TRUE(area == round(sqrt(3)*1000)/1000);
}

TEST(Triangle_methods, area_method_2) {
    Triangle t(Point(1,sqrt(3)), Point(-1,sqrt(3)), Point(0,2*sqrt(3)));
    double area = t.Area();
    ASSERT_TRUE(area == sqrt(3));
}

TEST(Triangle_methods, double_cast_method_1) {
    Triangle t(Point(0,0), Point(1,sqrt(3)), Point(-1,sqrt(3)));
    double temp = round(double(t) * 1000) / 1000;
    ASSERT_TRUE(temp == round(sqrt(3)*1000)/1000);
}

TEST(Triangle_methods, double_cast_method_2) {
    Triangle t(Point(1,sqrt(3)), Point(-1,sqrt(3)), Point(0,2*sqrt(3)));
    double temp = double(t);
    ASSERT_TRUE(temp == sqrt(3));
}

TEST(Triangle_operators, equality_operator) {
    Triangle t1(Point(1,sqrt(3)), Point(-1,sqrt(3)), Point(0,2*sqrt(3)));
    Triangle t2(Point(1,sqrt(3)), Point(-1,sqrt(3)), Point(0,2*sqrt(3)));
    ASSERT_TRUE(t1 == t2);
}

/*TEST(Triangle_operators, lvalue_copy_1) {
    Triangle t(Point(1,sqrt(3)), Point(-1,sqrt(3)), Point(0,2*sqrt(3)));
    Triangle New;
    New = t;
    ASSERT_TRUE(New == t);
}

TEST(Triangle_operators, lvalue_copy_2) {
    Triangle t;
    Square s(Point(0,0), Point(0,4), Point(4,4), Point(4,0));
    ASSERT_ANY_THROW(t = s);
}

TEST(Triangle_operators, rvalue_copy_1) {
    Triangle t(Point(1,sqrt(3)), Point(-1,sqrt(3)), Point(0,2*sqrt(3)));
    Triangle New1 = t;
    Triangle New2 = std::move(t);
    ASSERT_TRUE(New1 == New2);
}

TEST(Triangle_operators, rvalue_copy_2) {
    Triangle t;
    Square s(Point(0,0), Point(0,4), Point(4,4), Point(4,0));
    ASSERT_ANY_THROW(t = std::move(s));
}*/

TEST(Square_constructors, default_constructor) {
    Square s;
    ASSERT_TRUE(s.getname() == "Square");
}

TEST(Square_constructors, points_constructor_1) {
    ASSERT_ANY_THROW(Square s(Point(0, 0), Point(0,0), Point(1,1), Point(2,2)));
}

TEST(Square_constructos, points_constructor_2) {
    ASSERT_ANY_THROW(Square s(Point(1, 1), Point(2, 2), Point(3, 3), Point(4, 4)));
}

TEST(Square_construcors, points_constructor_3) {
    Square s(Point(-2, -2), Point(-2, 2), Point(2, 2), Point(2, -2));
}

TEST(Square_methods, center_method_1) {
    Square s(Point(-2, -2), Point(-2, 2), Point(2, 2), Point(2, -2));
    Point center = s.Center();
    ASSERT_TRUE(round(center.get_x_value()*1000)/1000 == 0 && round(center.get_y_value()*1000)/1000 == 0);
}

TEST(Square_methods, center_method_2) {
    Square s(Point(0,0), Point(0,4), Point(4,4), Point(4,0));
    Point center = s.Center();
    ASSERT_TRUE(round(center.get_x_value()*1000)/1000 == 2 && round(center.get_y_value()*1000)/1000 == 2);
}

TEST(Square_methods, area_method_1) {
    Square s(Point(-2, -2), Point(-2, 2), Point(2, 2), Point(2, -2));
    double area = s.Area();
    ASSERT_TRUE(area == 16);
}

TEST(Square_methods, area_method_2) {
    Square s(Point(0,0), Point(0,4), Point(4,4), Point(4,0));
    double area = s.Area();
    ASSERT_TRUE(area == 16);
}

TEST(Square_operators, double_cast_operator) {
    Square s(Point(0,0), Point(0,4), Point(4,4), Point(4,0));
    double temp = double(s);
    ASSERT_TRUE(temp == 16);
}

TEST(Square_operators, equality_operator) {
    Square s1(Point(0,0), Point(0,4), Point(4,4), Point(4,0));
    Square s2(Point(0,0), Point(0,4), Point(4,4), Point(4,0));
    ASSERT_TRUE(s1 == s2);
}

/*TEST(Square_operators, lvalue_copy) {
    Square s1(Point(0,0), Point(0,4), Point(4,4), Point(4,0));
    Square s2;
    s2 = s1;
    ASSERT_TRUE(s1 == s2);
}

TEST(Square_operators, rvalue_copy) {
    Square s1(Point(0,0), Point(0,4), Point(4,4), Point(4,0));
    Square s2;
    Square s3;
    s3 = s1;
    s2 = std::move(s1);
    ASSERT_TRUE(s2 == s3);
}*/

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}