#include "layer_pack.h"
#include <iostream>

// Конструктор с параметром по умолчанию (пустой пакет слоев)
LayerPack::LayerPack(std::vector<Layer> layers) : layers_by_index(std::move(layers)) {
    for (const auto& layer : layers_by_index) {
        layers_by_name[layer.get_name()] = layer; // Используйте get_name() для получения имени
    }
}

// Добавляет новый слой в конец списка и индексирует его по имени
void LayerPack::append_layer(const Layer& layer) {
    std::cout << "append_layer called: " << layer.get_name() << std::endl; // Используйте get_name()
    layers_by_index.push_back(layer);
    layers_by_name[layer.get_name()] = layer; // Индексируем по имени
}

// Удаляет слой по имени
void LayerPack::remove_layer(const std::string& name) {
    std::cout << "remove_layer called for layer: " << name << std::endl;
    auto it = layers_by_name.find(name);
    if (it != layers_by_name.end()) {
        // Удаление по имени также требует обновления в layers_by_index
        layers_by_index.erase(std::remove_if(layers_by_index.begin(), layers_by_index.end(),
            [&](const Layer& layer) { return layer.get_name() == name; }), layers_by_index.end());
        layers_by_name.erase(it);
    } else {
        throw std::invalid_argument("Layer not found: " + name);
    }
}

// Удаляет слой по индексу
void LayerPack::remove_layer(size_t index) {
    if (index < layers_by_index.size()) {
        std::cout << "remove_layer called for index: " << index << std::endl;
        std::string name = layers_by_index[index].get_name(); // Используйте get_name()
        layers_by_index.erase(layers_by_index.begin() + index);
        layers_by_name.erase(name);
    } else {
        throw std::out_of_range("Index out of range");
    }
}

// Возвращает ссылку на вектор слоев для доступа к слоям по индексу
const std::vector<Layer>& LayerPack::get_layers() const {
    std::cout << "get_layers called" << std::endl;
    return layers_by_index;
}

// Перегрузка оператора [] для доступа к слою по индексу
Layer& LayerPack::operator[](size_t index) {
    if (index < layers_by_index.size()) {
        std::cout << "Operator[] called for index: " << index << std::endl;
        return layers_by_index[index];
    }
    throw std::out_of_range("Index out of range");
}

const Layer& LayerPack::operator[](size_t index) const {
    if (index < layers_by_index.size()) {
        std::cout << "Operator[] const called for index: " << index << std::endl;
        return layers_by_index[index];
    }
    throw std::out_of_range("Index out of range");
}

// Перегрузка оператора [] для доступа к слою по имени
Layer& LayerPack::operator[](const std::string& name) {
    std::cout << "Operator[] called for layer name: " << name << std::endl;
    auto it = layers_by_name.find(name);
    if (it != layers_by_name.end()) {
        return it->second;
    }
    throw std::invalid_argument("Layer not found: " + name);
}

const Layer& LayerPack::operator[](const std::string& name) const {
    std::cout << "Operator[] const called for layer name: " << name << std::endl;
    auto it = layers_by_name.find(name);
    if (it != layers_by_name.end()) {
        return it->second;
    }
    throw std::invalid_argument("Layer not found: " + name);
}

// Возвращает словарь всех слоев в виде структуры данных
std::unordered_map<std::string, Layer> LayerPack::get_layers_by_name() const {
    std::cout << "get_layers_by_name called" << std::endl;
    return layers_by_name;
}
