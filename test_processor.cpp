#include <cassert>
#include <iostream>
#include "umformer.h"
#include "processor.h"

/*
Предполагается, что файл содержит корректные примеры, с которыми должны корректно отработать функции используемых модулей других разработчиков
В этом тестовом модуле првоеряется работа функций класса processor. 
При соблюдении условий выше, функции должны работать на корректных примерах(возвращать 0) и 
изменять соответсвующий layer_pack
*/

void test1(Processor processor, LayerPack& layer_pack) {

    int result = processor.doOperationWithLayers("Layer1", "Layer2", "Result1", layer_pack, OperationType::UNION);
    
    assert(result == 0);
    assert(checkName("Result1", layer_pack.get_layers_names()) == false);
    std::cout << "test1 passed.\n";
}

void test2(Processor processor, LayerPack& layer_pack) {

    int result = processor.doOperationWithLayers("Layer1", "Layer2", "Result2", layer_pack, OperationType::INTERSECTION);
    assert(result == 0);
    assert(checkName("Result2", layer_pack.get_layers_names()) == false);
    std::cout << "test2 passed.\n";
}

void test3(Processor processor, LayerPack& layer_pack) {

    int result = processor.doOperationWithLayers("Layer1", "Layer2", "Result3", layer_pack, OperationType::SUBTRACTION);
    assert(result == 0);
    assert(checkName("Result3", layer_pack.get_layers_names()) == false);
    std::cout << "test3 passed.\n";
}

void test4(Processor processor, LayerPack& source_layer_pack, LayerPack& target_layer_pack) {

    int result = processor.doOperationWithLayers("Layer1", "Layer2", "Result4", source_layer_pack, target_layer_pack, OperationType::UNION);
    assert(result == 0);
    assert(checkName("Result4", target_layer_pack.get_layers_names()) == false);
    std::cout << "test4 passed.\n";
}

void test5(Processor processor, LayerPack& source_layer_pack, LayerPack& target_layer_pack) {

    int result = processor.doOperationWithLayers("Layer1", "Layer2", "Result5", source_layer_pack, target_layer_pack, OperationType::INTERSECTION);
    assert(result == 0);
    assert(checkName("Result5", target_layer_pack.get_layers_names()) == false);
    std::cout << "test5 passed.\n";
}

void test6(Processor processor, LayerPack& source_layer_pack, LayerPack& target_layer_pack) {

    int result = processor.doOperationWithLayers("Layer1", "Layer2", "Result6", source_layer_pack, target_layer_pack, OperationType::SUBTRACTION);
    assert(result == 0);
    assert(checkName("Result6", target_layer_pack.get_layers_names()) == false);
    std::cout << "test6 passed.\n";
}

void test7(Processor processor, LayerPack& layer_pack) {

    int result = processor.expandLayer("Layer1", "Result7", 1.0, layer_pack);
    
    assert(result == 0);
    assert(checkName("Result7", layer_pack.get_layers_names()) == false);
    std::cout << "test7 passed.\n";
}

void test8(Processor processor, LayerPack& layer_pack) {
    int result = processor.shrinkLayer("Layer1", "Result8", 1.0, layer_pack);
    
    assert(result == 0);
    assert(checkName("Result8", layer_pack.get_layers_names()) == false);
    std::cout << "test8 passed.\n";
}

void test9(Processor processor, LayerPack& layer_pack) {
    
    int result = processor.copyLayer("Layer1", "Result9", layer_pack);
    
    assert(result == 0);
    assert(layer_pack.get_layers_names().back() == "CopiedLayer");
    std::cout << "test9 passed.\n";
}

void test10(Processor processor, LayerPack& layer_pack) {
    
    int result = processor.layerHaveFigure("Layer1", layer_pack);
    
    assert(result == 1);
    std::cout << "test10 passed.\n";
}

void test11(Processor processor, LayerPack& layer_pack) {
    
    int result = processor.layerHaveFigure("Layer3", layer_pack);
    
    assert(result == 0);
    std::cout << "test11 passed.\n";
}

void test12(Processor processor, LayerPack& layer_pack) {

    int result = processor.doOperationWithLayers("Layer1", "Layer2", "Result1", layer_pack, OperationType::UNION);
    
    assert(result == 0);
    std::cout << "test12 passed.\n";
}

int main() {
    Converter source_converter;
    source_converter.loadJson("test.json");
    LayerPack& source_layer_pack = source_converter.getLayerPack();

    Converter target_converter;
    target_converter.loadJson("target.json");
    LayerPack& target_layer_pack = target_converter.getLayerPack();

    Processor processor;
    test1(processor, source_layer_pack);
    test2(processor, source_layer_pack);
    test3(processor, source_layer_pack);
    test4(processor, source_layer_pack, target_layer_pack);
    test5(processor, source_layer_pack, target_layer_pack);
    test6(processor, source_layer_pack, target_layer_pack);
    std::cout << "All tests passed.\n";
    return 0;
}
