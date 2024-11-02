#include "converter.h"
#include <iostream>

// Метод для конвертации данных из JSON-файла
void Converter::convertJson(const std::string& filename) {
    std::cout << "convertJson called with filename: " << filename << std::endl;
    // Здесь должна быть логика для конвертации из JSON в LayerPack
    // Временно оставим пустым
}

// Метод для сохранения данных в JSON-файл
void Converter::saveToJson(const std::string& filename) {
    std::cout << "saveToJson called with filename: " << filename << std::endl;
    // Здесь должна быть логика для сохранения LayerPack в JSON
    // Временно оставим пустым
}

// Метод для получения ссылки на LayerPack
LayerPack& Converter::getLayerPack() {
    std::cout << "getLayerPack called" << std::endl;
    return layerpack; // Возвращаем ссылку на layerpack
}
