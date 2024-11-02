#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <string>
#include "layer_pack.h"
#include "converter.h"
#include "operations.h"

class Processor {
public:
    int uniteLayers(const std::string& first_layer_name, const std::string& second_layer_name, const std::string& result_layer_name, const std::string& source_file_name, const std::string& target_file_name);

    int intersectLayers(const std::string& first_layer_name, const std::string& second_layer_name, const std::string& result_layer_name, const std::string& source_file_name, const std::string& target_file_name);

    int subtractLayers(const std::string& first_layer_name, const std::string& second_layer_name, const std::string& result_layer_name, const std::string& source_file_name, const std::string& target_file_name);

    int expandLayer(const std::string& layer_name, const std::string& result_layer_name, float size, const std::string& source_file_name, const std::string& target_file_name);

    int shrinkLayer(const std::string& layer_name, const std::string& result_layer_name, float size, const std::string& source_file_name, const std::string& target_file_name);

    int delLayer(const std::string& layer_name, const std::string& layout_file_name);

    int renameLayer(const std::string& old_layer_name, const std::string& new_layer_name, const std::string& layout_file_name);

    int copyLayer(const std::string& layer_name, const std::string& copy_layer_name, const std::string& source_file_name, const std::string& target_file_name);

    int layerHaveFigure(const std::string& layer_name, const std::string& layout_file_name);
};

#endif // PROCESSOR_H
