#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>
#include "layer_pack.h"
#include "converter.h"
#include "operations.h" // Подключение вспомогательных методов для обработки полигонов

class Processor {
public:
    // Метод для объединения двух слоев
    int uniteLayers(const std::string& first_layer_name, const std::string& second_layer_name, const std::string& result_layer_name, const std::string& source_file_name, const std::string& target_file_name);

    // Метод для пересечения двух слоев
    int intersectLayers(const std::string& first_layer_name, const std::string& second_layer_name, const std::string& result_layer_name, const std::string& source_file_name, const std::string& target_file_name);

    // Метод для вычитания слоев
    int subtractLayers(const std::string& first_layer_name, const std::string& second_layer_name, const std::string& result_layer_name, const std::string& source_file_name, const std::string& target_file_name);

    // Метод для расширения слоя
    int expandLayer(const std::string& layer_name, const std::string& result_layer_name, float size, const std::string& source_file_name, const std::string& target_file_name);

    // Метод для сужения слоя
    int shrinkLayer(const std::string& layer_name, const std::string& result_layer_name, float size, const std::string& source_file_name, const std::string& target_file_name);

    // Метод для удаления слоя
    int delLayer(const std::string& layer_name, const std::string& layout_file_name);

    // Метод для переименования слоя
    int renameLayer(const std::string& old_layer_name, const std::string& new_layer_name, const std::string& layout_file_name);

    // Метод для копирования слоя
    int copyLayer(const std::string& layer_name, const std::string& copy_layer_name, const std::string& source_file_name, const std::string& target_file_name);

    // Метод для проверки наличия фигур в слое
    int layerHaveFigure(const std::string& layer_name, const std::string& layout_file_name);
};

#endif // PROCESSOR_H
