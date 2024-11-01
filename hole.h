#ifndef HOLE_H
#define HOLE_H

#include <vector>
#include <unordered_map>
#include <variant>
#include "point.h"  // Предполагается, что этот файл определяет класс Point

class Hole {
private:
    std::vector<Point> vertices;  // Вектор вершин, определяющий форму дырки

public:
    // Конструктор с параметрами по умолчанию (пустая дырка)
    Hole(const std::vector<Point>& vertices = {});

    // Добавляет точку в конец вектора вершин дырки
    void append(const Point& point);

    // Вставляет точку на определенную позицию в вектор вершин
    void insert(const Point& point, size_t index);

    // Удаляет точку из вектора вершин по указанной позиции
    void remove(size_t index);

    // Возвращает ссылку на вектор точек дырки
    const std::vector<Point>& get_vertices() const;

    // Перегрузка оператора [] для доступа к вершинам по индексу
    Point& operator[](size_t index);
    const Point& operator[](size_t index) const;

    // Возвращает структуру объекта Hole в виде "словаря" (для сериализации)
    std::unordered_map<std::string, VariantType> ravel() const;
};

#endif // HOLE_H
