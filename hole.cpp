#include "hole.h"
#include <iostream>

// Конструктор с параметрами по умолчанию (пустая дырка)
Hole::Hole(const std::vector<Point>& vertices) 
    : vertices(vertices) {}

// Добавляет точку в конец вектора вершин дырки
void Hole::append(const Point& point) {
    std::cout << "append called for point" << std::endl;
    vertices.push_back(point);
}

// Вставляет точку на определенную позицию в вектор вершин
void Hole::insert(const Point& point, size_t index) {
    std::cout << "insert called for point at index: " << index << std::endl;
    if (index <= vertices.size()) { // Убедитесь, что индекс не выходит за пределы
        vertices.insert(vertices.begin() + index, point);
    } else {
        throw std::out_of_range("Index out of range");
    }
}

// Удаляет точку из вектора вершин по указанной позиции
void Hole::remove(size_t index) {
    std::cout << "remove called for index: " << index << std::endl;
    if (index < vertices.size()) {
        vertices.erase(vertices.begin() + index);
    } else {
        throw std::out_of_range("Index out of range");
    }
}

// Возвращает ссылку на вектор точек дырки
const std::vector<Point>& Hole::get_vertices() const {
    std::cout << "get_vertices called" << std::endl;
    return vertices;
}

// Перегрузка оператора [] для доступа к вершинам по индексу
Point& Hole::operator[](size_t index) {
    if (index < vertices.size()) {
        std::cout << "Operator[] called for index: " << index << std::endl;
        return vertices[index];
    }
    throw std::out_of_range("Index out of range");
}

const Point& Hole::operator[](size_t index) const {
    if (index < vertices.size()) {
        std::cout << "Operator[] const called for index: " << index << std::endl;
        return vertices[index];
    }
    throw std::out_of_range("Index out of range");
}

// Возвращает структуру объекта Hole в виде "словаря" (для сериализации)
std::unordered_map<std::string, VariantType> Hole::ravel() const {
    std::cout << "ravel called" << std::endl;
    std::unordered_map<std::string, VariantType> result;
    result["vertices_count"] = static_cast<int>(vertices.size()); // добавление количества вершин
    // Можно добавить другие поля, если необходимо
    return result;
}
