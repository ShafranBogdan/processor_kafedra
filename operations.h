#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <vector>
#include <string>
#include "polygon.h"
#include "layer.h"
#include "layer_pack.h"

enum class OperationType {
    UNION,
    INTERSECTION,
    SUBTRACTION
};

namespace PolygonOperations {

    // Функция для обработки полигонов с операциями объединения, пересечения и вычитания
    std::vector<Polygon> processPolygons(const std::vector<Polygon>& polygons1, const std::vector<Polygon>& polygons2, OperationType operation);

    // Функция для модификации полигонов слоя: расширения или сжатия в зависимости от знака size
    std::vector<Polygon> modifyPolygons(const std::vector<Polygon>& polygons, float size);
}

namespace LayerOperations {
    
    // Проверка корректности слоя
    bool checkLayer(const Layer& layer);

    // Удаление слоя с именем layer_name из layer_pack
    LayerPack delLayerInLayerPack(const std::string& layer_name, LayerPack& layer_pack);

    // Переименование слоя в layer_pack
    LayerPack renameLayerInLayerPack(const std::string& old_layer_name, const std::string& new_layer_name, LayerPack& layer_pack);

    // Проверка наличия фигур в слое
    bool layerIsEmpty(Layer& layer);

    // Копирование слоя с именем source_layer_name из одного LayerPack в другой LayerPack
    LayerPack copyLayerFromLayerPack(const LayerPack& layer_pack1, const LayerPack& layer_pack2, const std::string& source_layer_name, const std::string& target_layer_name);
}

#endif // OPERATIONS_H
