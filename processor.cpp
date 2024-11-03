#include "processor.h"
#include <iostream>

int Processor::uniteLayers(const std::string& first_layer_name, const std::string& second_layer_name,
                           const std::string& result_layer_name, const std::string& source_file_name,
                           const std::string& target_file_name) {
    try {
        Converter source_converter;
        source_converter.convertJson(source_file_name);
        LayerPack& source_layer_pack = source_converter.getLayerPack();

        Layer& first_layer = source_layer_pack[first_layer_name];
        Layer& second_layer = source_layer_pack[second_layer_name];

        const std::vector<Polygon>& polygons1 = first_layer.get_polygons();
        const std::vector<Polygon>& polygons2 = second_layer.get_polygons();

        std::vector<Polygon> result_polygons = PolygonOperations::processPolygons(polygons1, polygons2, OperationType::UNION);

        Layer result_layer(result_layer_name, result_polygons);
        if (target_file_name == source_file_name) {
            source_layer_pack.append_layer(result_layer);
            source_converter.saveToJson(target_file_name);
        }
        else {
            Converter target_converter;
            target_converter.convertJson(target_file_name);
            LayerPack& target_layer_pack = target_converter.getLayerPack();
            target_layer_pack.append_layer(result_layer);
            target_converter.saveToJson(target_file_name);
        }
        return 0;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
}

int Processor::intersectLayers(const std::string& first_layer_name, const std::string& second_layer_name,
                               const std::string& result_layer_name, const std::string& source_file_name,
                               const std::string& target_file_name) {
    try {
        Converter source_converter;
        source_converter.convertJson(source_file_name);
        LayerPack& source_layer_pack = source_converter.getLayerPack();

        Layer& first_layer = source_layer_pack[first_layer_name];
        Layer& second_layer = source_layer_pack[second_layer_name];

        const std::vector<Polygon>& polygons1 = first_layer.get_polygons();
        const std::vector<Polygon>& polygons2 = second_layer.get_polygons();

        std::vector<Polygon> result_polygons = PolygonOperations::processPolygons(polygons1, polygons2, OperationType::INTERSECTION);

        Layer result_layer(result_layer_name, result_polygons);
        if (target_file_name == source_file_name) {
            source_layer_pack.append_layer(result_layer);
            source_converter.saveToJson(target_file_name);
        }
        else {
            Converter target_converter;
            target_converter.convertJson(target_file_name);
            LayerPack& target_layer_pack = target_converter.getLayerPack();
            target_layer_pack.append_layer(result_layer);
            target_converter.saveToJson(target_file_name);
        }
        return 0;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
}

int Processor::subtractLayers(const std::string& first_layer_name, const std::string& second_layer_name,
                              const std::string& result_layer_name, const std::string& source_file_name,
                              const std::string& target_file_name) {
    try {
        Converter source_converter;
        source_converter.convertJson(source_file_name);
        LayerPack& source_layer_pack = source_converter.getLayerPack();

        Layer& first_layer = source_layer_pack[first_layer_name];
        Layer& second_layer = source_layer_pack[second_layer_name];

        const std::vector<Polygon>& polygons1 = first_layer.get_polygons();
        const std::vector<Polygon>& polygons2 = second_layer.get_polygons();

        std::vector<Polygon> result_polygons = PolygonOperations::processPolygons(polygons1, polygons2, OperationType::SUBTRACTION);

        Layer result_layer(result_layer_name, result_polygons);
        if (target_file_name == source_file_name) {
            source_layer_pack.append_layer(result_layer);
            source_converter.saveToJson(target_file_name);
        }
        else {
            Converter target_converter;
            target_converter.convertJson(target_file_name);
            LayerPack& target_layer_pack = target_converter.getLayerPack();
            target_layer_pack.append_layer(result_layer);
            target_converter.saveToJson(target_file_name);
        }
        return 0;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
}

int Processor::expandLayer(const std::string& layer_name, const std::string& result_layer_name, float size,
                           const std::string& source_file_name, const std::string& target_file_name) {
    try {
        Converter source_converter;
        source_converter.convertJson(source_file_name);
        LayerPack& source_layer_pack = source_converter.getLayerPack();

        Layer& layer = source_layer_pack[layer_name];

        const std::vector<Polygon>& polygons = layer.get_polygons();

        std::vector<Polygon> result_polygons = PolygonOperations::modifyPolygons(polygons, size);

        Layer result_layer(result_layer_name, result_polygons);
        if (target_file_name == source_file_name && layer_name == result_layer_name) {
            layer = result_layer;
        }
        else {
            if (target_file_name == source_file_name) {
                source_layer_pack.append_layer(result_layer);
                source_converter.saveToJson(target_file_name);
            }
            else {
                Converter target_converter;
                target_converter.convertJson(target_file_name);
                LayerPack& target_layer_pack = target_converter.getLayerPack();
                target_layer_pack.append_layer(result_layer);
                target_converter.saveToJson(target_file_name);
            }
        }
        return 0;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
}

int Processor::shrinkLayer(const std::string& layer_name, const std::string& result_layer_name, float size,
                           const std::string& source_file_name, const std::string& target_file_name) {
    return expandLayer(layer_name, result_layer_name, -size, source_file_name, target_file_name);
}

int Processor::delLayer(const std::string& layer_name, const std::string& layout_file_name) {
    try {
        Converter converter;
        converter.convertJson(layout_file_name);
        LayerPack& layer_pack = converter.getLayerPack();

        layer_pack = LayerOperations::delLayerInLayerPack(layer_name, layer_pack);
        converter.saveToJson(layout_file_name);

        return 0;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
}

int Processor::renameLayer(const std::string& old_layer_name, const std::string& new_layer_name,
                           const std::string& layout_file_name) {
    try {
        Converter converter;
        converter.convertJson(layout_file_name);
        LayerPack& layer_pack = converter.getLayerPack();

        layer_pack = LayerOperations::renameLayerInLayerPack(old_layer_name, new_layer_name, layer_pack);
        converter.saveToJson(layout_file_name);

        return 0;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
}

int Processor::copyLayer(const std::string& layer_name, const std::string& copy_layer_name,
                         const std::string& source_file_name, const std::string& target_file_name) {
    try {
        Converter source_converter;
        source_converter.convertJson(source_file_name);
        LayerPack& source_layer_pack = source_converter.getLayerPack();

        if (target_file_name == source_file_name) {
            if (copy_layer_name == layer_name)
            {
                throw std::invalid_argument("Имя копируемого слоя совпадает с исходным именем при одинаковых именах входного и выходного файла. Укажите другое имя для копии.");
            }
            source_layer_pack = LayerOperations::copyLayerFromLayerPack(source_layer_pack, layer_name, copy_layer_name);
            source_converter.saveToJson(target_file_name);
        }
        else {
            Converter target_converter;
            target_converter.convertJson(target_file_name);
            LayerPack& target_layer_pack = target_converter.getLayerPack();
            target_layer_pack = LayerOperations::copyLayerFromLayerPack(source_layer_pack, layer_name, copy_layer_name);
            target_converter.saveToJson(target_file_name);
        }
        return 0;
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
}

int Processor::layerHaveFigure(const std::string& layer_name, const std::string& layout_file_name) {
    try {
        Converter converter;
        converter.convertJson(layout_file_name);
        LayerPack& layer_pack = converter.getLayerPack();

        Layer& layer = layer_pack[layer_name];

        if (LayerOperations::layerIsEmpty(layer)) {
            return 1;
        } else {
            return 0;
        }
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }
}