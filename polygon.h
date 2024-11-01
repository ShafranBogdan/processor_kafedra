#ifndef POLYGON_H
#define POLYGON_H

#include <vector>
#include <unordered_map>
#include "point.h"    // Предполагается, что этот файл определяет класс Point
#include "hole.h"     // Предполагается, что этот файл определяет класс Hole

class Polygon {
private:
    std::vector<Point> vertices;      // Вектор вершин полигона
    std::vector<Hole> holes;          // Вектор дырок внутри полигона

public:
    // Конструктор с параметрами по умолчанию (пустой полигон)
    Polygon(const std::vector<Point>& vertices = {}, const std::vector<Hole>& holes = {});

    // Добавляет точку в конец вектора вершин полигона
    void append(const Point& point);

    // Вставляет точку на определенную позицию в вектор вершин
    void insert(const Point& point, size_t index);

    // Удаляет точку из вектора вершин по указанной позиции
    void remove(size_t index);

    // Возвращает ссылку на вектор точек полигона
    const std::vector<Point>& get_vertices() const;

    // Перегрузка оператора [] для доступа к вершинам по индексу
    Point& operator[](size_t index);
    const Point& operator[](size_t index) const;

    // Методы работы с дырками
    void add_hole(const Hole& hole);             // Добавляет дырку в полигон
    void remove_hole(size_t index);              // Удаляет дырку по индексу
    const std::vector<Hole>& get_holes() const;  // Возвращает ссылку на вектор дырок

    // Возвращает структуру объекта Polygon, включая его вершины и дырки, в виде "словаря" (для сериализации)
    std::unordered_map<std::string, VariantType> ravel() const;
};

#endif // POLYGON_H
