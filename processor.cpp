#include "processor.h"
#include <iostream>

int Processor::uniteLayers(const std::string& first_layer_name, const std::string& second_layer_name,
                           const std::string& result_layer_name, const std::string& source_file_name,
                           const std::string& target_file_name) {
    std::cout << "hello" << std::endl;
    return 0;
}

int Processor::intersectLayers(const std::string& first_layer_name, const std::string& second_layer_name,
                               const std::string& result_layer_name, const std::string& source_file_name,
                               const std::string& target_file_name) {
    std::cout << "hello" << std::endl;
    return 0;
}

int Processor::subtractLayers(const std::string& first_layer_name, const std::string& second_layer_name,
                              const std::string& result_layer_name, const std::string& source_file_name,
                              const std::string& target_file_name) {
    std::cout << "hello" << std::endl;
    return 0;
}

int Processor::expandLayer(const std::string& layer_name, const std::string& result_layer_name, float size,
                           const std::string& source_file_name, const std::string& target_file_name) {
    std::cout << "hello" << std::endl;
    return 0;
}

int Processor::shrinkLayer(const std::string& layer_name, const std::string& result_layer_name, float size,
                           const std::string& source_file_name, const std::string& target_file_name) {
    std::cout << "hello" << std::endl;
    return 0;
}

int Processor::delLayer(const std::string& layer_name, const std::string& layout_file_name) {
    std::cout << "hello" << std::endl;
    return 0;
}

int Processor::renameLayer(const std::string& old_layer_name, const std::string& new_layer_name,
                           const std::string& layout_file_name) {
    std::cout << "hello" << std::endl;
    return 0;
}

int Processor::copyLayer(const std::string& layer_name, const std::string& copy_layer_name,
                         const std::string& source_file_name, const std::string& target_file_name) {
    std::cout << "hello" << std::endl;
    return 0;
}

int Processor::layerHaveFigure(const std::string& layer_name, const std::string& layout_file_name) {
    std::cout << "hello" << std::endl;
    return 0;
}
