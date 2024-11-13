#ifndef UMFORMER_H
#define UMFORMER_H

//#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "include/rapidjson/filereadstream.h"
#include "include/rapidjson/filewritestream.h"
#include "include/rapidjson/document.h"
#include "include/rapidjson/prettywriter.h"
#include "include/rapidjson/stringbuffer.h"
#include "include/rapidjson/error/en.h"
#include "Entity.h"


using namespace std; 
using namespace rapidjson;

#define BUFF_SIZE 65536

// Класс для разбора JSON-файла
class Converter {
    LayerPack layerpack;
public:
    // Метод для загрузки и разбора JSON
    Converter() {};
    void loadJson(const std::string& filename);
    void saveToJson(const std::string& filename);
    LayerPack& getLayerPack();
};

#endif 