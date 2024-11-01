#ifndef CONVERTER_H
#define CONVERTER_H

#include <string>
#include "layer_pack.h"

class Converter {
private:
    LayerPack layerpack;

public:
    Converter() = default;

    void convertJson(const std::string& filename);

    void saveToJson(const std::string& filename);

    LayerPack& getLayerPack();
};

#endif // CONVERTER_H
