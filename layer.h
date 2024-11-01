#ifndef LAYER_H
#define LAYER_H

#include <string>
#include <vector>
#include <unordered_map>
#include "polygon.h" // Предполагается, что этот файл определяет класс Polygon

class Layer {
private:
    std::string name;                 // Имя слоя
    std::vector<Polygon> polygons;    // Вектор полигонов, принадлежащих слою

public:
    // Конструктор с параметрами по умолчанию (пустой слой)
    Layer(const std::string& name, const std::vector<Polygon>& polygons = {});

    // Возвращает имя слоя
    const std::string& get_name() const;

    // Переименовывает слой
    void rename(const std::string& new_name);

    // Добавляет полигон в конец списка
    void append(const Polygon& polygon);

    // Вставляет полигон на указанную позицию
    void insert(const Polygon& polygon, size_t index);

    // Удаляет полигон по индексу
    void remove(size_t index);

    // Возвращает ссылку на вектор полигонов для доступа к ним
    const std::vector<Polygon>& get_polygons() const;

    // Перегрузка оператора [] для доступа к полигону по индексу
    Polygon& operator[](size_t index);
    const Polygon& operator[](size_t index) const;

    // Возвращает структуру объекта Layer в виде "словаря" (для сериализации)
    std::unordered_map<std::string, VariantType> ravel() const;
};

#endif // LAYER_H
