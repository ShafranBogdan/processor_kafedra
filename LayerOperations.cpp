#include "LayerOperations.h"
#include <algorithm>
#include <stdexcept>
#include <unordered_set>

namespace LayerOperations {

    bool checkLayer(const Layer& layer) {
        std::unordered_set<int> unique_ids;
        
        // Явное указание типа итератора
        for (std::vector<Figure>::const_iterator it = layer.figures.begin(); it != layer.figures.end(); ++it) {
            const Figure& figure = *it;
            
            // Проверка уникальности идентификатора фигуры
            if (unique_ids.find(figure.id) != unique_ids.end()) {
                return false;  // Дублирующийся идентификатор
            }
            unique_ids.insert(figure.id);

            // Проверка корректности значений атрибутов фигуры
            // Здесь можно добавить проверки диапазонов координат, размеров и т.д.
            // Например: if (figure.coordinate < MIN || figure.coordinate > MAX) return false;
        }

        return true;  // Все проверки пройдены
    }

    LayerPack delLayerInLayerPack(const std::string& layer_name, LayerPack& layer_pack) {
        // Явное указание типа итератора
        std::vector<Layer>::iterator it = std::remove_if(layer_pack.layers.begin(), layer_pack.layers.end(),
            [&layer_name](const Layer& layer) { return layer.name == layer_name; });

        if (it != layer_pack.layers.end()) {
            layer_pack.layers.erase(it, layer_pack.layers.end());  // Удаление найденного слоя
        }
        
        return layer_pack;  // Возвращаем обновленную копию LayerPack
    }

    LayerPack renameLayerInLayerPack(const std::string& old_layer_name, const std::string& new_layer_name, LayerPack& layer_pack) {
        // Явное указание типа итератора
        std::vector<Layer>::iterator it = std::find_if(layer_pack.layers.begin(), layer_pack.layers.end(),
            [&old_layer_name](const Layer& layer) { return layer.name == old_layer_name; });

        if (it != layer_pack.layers.end()) {
            it->name = new_layer_name;  // Переименование слоя
        } else {
            throw std::invalid_argument("Layer with name " + old_layer_name + " not found.");
        }

        return layer_pack;  // Возвращаем обновленную копию LayerPack
    }

} // namespace LayerOperations



