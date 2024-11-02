#include "point.h"
#include <iostream>

// Конструктор инициализирует точку с заданными координатами (x, y)
Point::Point(double x, double y) : x(x), y(y) {
    std::cout << "Point constructor called with x = " << x << ", y = " << y << std::endl;
}

// Оператор сложения, возвращающий новую точку, являющуюся суммой текущей и другой точки
Point Point::operator+(const Point& other) const {
    std::cout << "operator+ called" << std::endl;
    return Point(x + other.x, y + other.y);
}

// Оператор вычитания, возвращающий новую точку, являющуюся разностью текущей и другой точки
Point Point::operator-(const Point& other) const {
    std::cout << "operator- called" << std::endl;
    return Point(x - other.x, y - other.y);
}

// Возвращает структуру объекта Point в виде "словаря" с его полями
std::unordered_map<std::string, double> Point::ravel() const {
    std::cout << "ravel called" << std::endl;
    return {{"x", x}, {"y", y}};
}
