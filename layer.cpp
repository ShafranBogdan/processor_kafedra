#include "layer.h"
#include <iostream>

// Конструктор с параметрами по умолчанию (пустой слой)
Layer::Layer(const std::string& name, const std::vector<Polygon>& polygons) 
    : name(name), polygons(polygons) {}

// Возвращает имя слоя
const std::string& Layer::get_name() const {
    std::cout << "get_name called: " << name << std::endl;
    return name;
}

// Переименовывает слой
void Layer::rename(const std::string& new_name) {
    std::cout << "rename called: " << name << " to " << new_name << std::endl;
    name = new_name;
}

// Добавляет полигон в конец списка
void Layer::append(const Polygon& polygon) {
    std::cout << "append called for polygon" << std::endl;
    polygons.push_back(polygon);
}

// Вставляет полигон на указанную позицию
void Layer::insert(const Polygon& polygon, size_t index) {
    std::cout << "insert called for polygon at index: " << index << std::endl;
    if (index <= polygons.size()) { // Убедитесь, что индекс не выходит за пределы
        polygons.insert(polygons.begin() + index, polygon);
    } else {
        throw std::out_of_range("Index out of range");
    }
}

// Удаляет полигон по индексу
void Layer::remove(size_t index) {
    std::cout << "remove called for index: " << index << std::endl;
    if (index < polygons.size()) {
        polygons.erase(polygons.begin() + index);
    } else {
        throw std::out_of_range("Index out of range");
    }
}

// Возвращает ссылку на вектор полигонов для доступа к ним
const std::vector<Polygon>& Layer::get_polygons() const {
    std::cout << "get_polygons called" << std::endl;
    return polygons;
}

// Перегрузка оператора [] для доступа к полигону по индексу
Polygon& Layer::operator[](size_t index) {
    if (index < polygons.size()) {
        std::cout << "Operator[] called for index: " << index << std::endl;
        return polygons[index];
    }
    throw std::out_of_range("Index out of range");
}

const Polygon& Layer::operator[](size_t index) const {
    if (index < polygons.size()) {
        std::cout << "Operator[] const called for index: " << index << std::endl;
        return polygons[index];
    }
    throw std::out_of_range("Index out of range");
}

// Возвращает структуру объекта Layer в виде "словаря" (для сериализации)
std::unordered_map<std::string, VariantType> Layer::ravel() const {
    std::cout << "ravel called for layer: " << name << std::endl;
    // Предполагается, что VariantType имеет возможность хранения различных типов данных.
    // Реализация ravel должна включать в себя возвращение необходимых данных о слое.
    std::unordered_map<std::string, VariantType> result;
    result["name"] = name; // добавление имени слоя
    // Добавьте другие поля, если необходимо
    return result;
}
