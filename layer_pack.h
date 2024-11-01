#ifndef LAYERPACK_H
#define LAYERPACK_H

#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include "layer.h" // Предполагается, что этот файл определяет класс Layer

class LayerPack {
private:
    std::unordered_map<std::string, Layer> layers_by_name; // Контейнер для доступа к слоям по имени
    std::vector<Layer> layers_by_index;                    // Контейнер для хранения слоев по индексу

public:
    // Конструктор с параметром по умолчанию (пустой пакет слоев)
    LayerPack(std::vector<Layer> layers = {});

    // Добавляет новый слой в конец списка и индексирует его по имени
    void append_layer(const Layer& layer);

    // Удаляет слой по имени
    void remove_layer(const std::string& name);

    // Удаляет слой по индексу
    void remove_layer(size_t index);

    // Возвращает ссылку на вектор слоев для доступа к слоям по индексу
    const std::vector<Layer>& get_layers() const;

    // Перегрузка оператора [] для доступа к слою по индексу
    Layer& operator[](size_t index);
    const Layer& operator[](size_t index) const;

    // Перегрузка оператора [] для доступа к слою по имени
    Layer& operator[](const std::string& name);
    const Layer& operator[](const std::string& name) const;

    // Возвращает словарь всех слоев в виде структуры данных
    std::unordered_map<std::string, Layer> get_layers_by_name() const;
};

#endif // LAYERPACK_H
