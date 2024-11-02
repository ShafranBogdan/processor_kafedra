#include "polygon.h"
#include <iostream>

// Конструктор с параметрами по умолчанию (пустой полигон)
Polygon::Polygon(const std::vector<Point>& vertices, const std::vector<Hole>& holes)
    : vertices(vertices), holes(holes) {
    std::cout << "Polygon constructor called" << std::endl;
}

// Добавляет точку в конец вектора вершин полигона
void Polygon::append(const Point& point) {
    vertices.push_back(point);
    std::cout << "append called" << std::endl;
}

// Вставляет точку на определенную позицию в вектор вершин
void Polygon::insert(const Point& point, size_t index) {
    if (index <= vertices.size()) {
        vertices.insert(vertices.begin() + index, point);
        std::cout << "insert called at index " << index << std::endl;
    } else {
        std::cout << "insert index out of bounds" << std::endl;
    }
}

// Удаляет точку из вектора вершин по указанной позиции
void Polygon::remove(size_t index) {
    if (index < vertices.size()) {
        vertices.erase(vertices.begin() + index);
        std::cout << "remove called at index " << index << std::endl;
    } else {
        std::cout << "remove index out of bounds" << std::endl;
    }
}

// Возвращает ссылку на вектор точек полигона
const std::vector<Point>& Polygon::get_vertices() const {
    std::cout << "get_vertices called" << std::endl;
    return vertices;
}

// Перегрузка оператора [] для доступа к вершинам по индексу
Point& Polygon::operator[](size_t index) {
    std::cout << "operator[] called for index " << index << std::endl;
    return vertices[index];
}

const Point& Polygon::operator[](size_t index) const {
    std::cout << "operator[] const called for index " << index << std::endl;
    return vertices[index];
}

// Добавляет дырку в полигон
void Polygon::add_hole(const Hole& hole) {
    holes.push_back(hole);
    std::cout << "add_hole called" << std::endl;
}

// Удаляет дырку по индексу
void Polygon::remove_hole(size_t index) {
    if (index < holes.size()) {
        holes.erase(holes.begin() + index);
        std::cout << "remove_hole called at index " << index << std::endl;
    } else {
        std::cout << "remove_hole index out of bounds" << std::endl;
    }
}

// Возвращает ссылку на вектор дырок
const std::vector<Hole>& Polygon::get_holes() const {
    std::cout << "get_holes called" << std::endl;
    return holes;
}

// Возвращает структуру объекта Polygon, включая его вершины и дырки, в виде "словаря" (для сериализации)
std::unordered_map<std::string, VariantType> Polygon::ravel() const {
    std::cout << "ravel called" << std::endl;
    // Возвращаем пустую карту, так как реализация сериализации не требуется
    return {};
}
