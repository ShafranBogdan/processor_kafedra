#ifndef LAYEROPERATIONS_H
#define LAYEROPERATIONS_H

#include <string>
#include <vector>
#include <unordered_set>
#include "Entity.h"

namespace LayerOperations {
    bool checkLayer(const Layer& layer);
    LayerPack delLayerInLayerPack(const std::string& layer_name, LayerPack& layer_pack);
    LayerPack renameLayerInLayerPack(const std::string& old_layer_name, const std::string& new_layer_name, LayerPack& layer_pack);
}

#endif // LAYEROPERATIONS_H
