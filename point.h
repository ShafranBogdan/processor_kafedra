#ifndef POINT_H
#define POINT_H

#include <unordered_map>
#include <string>

class Point {
public:
    double x;  // Координата точки по оси X
    double y;  // Координата точки по оси Y

    // Конструктор инициализирует точку с заданными координатами (x, y)
    Point(double x = 0.0, double y = 0.0);

    // Оператор сложения, возвращающий новую точку, являющуюся суммой текущей и другой точки
    Point operator+(const Point& other) const;

    // Оператор вычитания, возвращающий новую точку, являющуюся разностью текущей и другой точки
    Point operator-(const Point& other) const;

    // Возвращает структуру объекта Point в виде "словаря" с его полями
    std::unordered_map<std::string, double> ravel() const;
};

#endif // POINT_H
