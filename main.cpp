#include <iostream>
#include <string>
#include "processor.h"

void printUsage() {
    std::cout << "Usage:\n"
              << "  ./processor source_file_name L1 <operation> L2 to L3 [-o target_file_name]\n"
              << "  ./processor source_file_name L1 <operation> size to L2 [-o target_file_name]\n\n"
              << "Commands:\n"
              << "  unite:      ./processor source_file_name L1 unite L2 to L3 [-o target_file_name]\n"
              << "              Performs union of layers L1 and L2 from source_file_name, saves to L3.\n"
              << "              By default, saves in source_file_name if -o target_file_name is omitted.\n\n"
              << "  intersect:  ./processor source_file_name L1 intersect L2 to L3 [-o target_file_name]\n"
              << "              Performs intersection of layers L1 and L2 from source_file_name, saves to L3.\n"
              << "              By default, saves in source_file_name if -o target_file_name is omitted.\n\n"
              << "  subtract:   ./processor source_file_name L1 subtract L2 to L3 [-o target_file_name]\n"
              << "              Subtracts layer L2 from L1 in source_file_name, saves result to L3.\n"
              << "              By default, saves in source_file_name if -o target_file_name is omitted.\n\n"
              << "  expand:     ./processor source_file_name L1 expand size to L2 [-o target_file_name]\n"
              << "              Expands all polygons in layer L1 by 'size', saves to L2.\n"
              << "              By default, saves in source_file_name if -o target_file_name is omitted.\n\n"
              << "  shrink:     ./processor source_file_name L1 shrink size to L2 [-o target_file_name]\n"
              << "              Shrinks all polygons in layer L1 by 'size', saves to L2.\n"
              << "              If target_file_name and L2 are omitted, results are saved in L1.\n\n"
              << "  del_layer:  ./processor layout_file_name del_layer L1\n"
              << "              Deletes layer L1 from layout_file_name.\n\n"
              << "  rename_layer: ./processor layout_file_name rename_layer old_layer_name new_layer_name\n"
              << "              Renames old_layer_name to new_layer_name in layout_file_name.\n\n"
              << "  copy_layer: ./processor source_file_name copy_layer L1 to L2 [-o target_file_name]\n"
              << "              Copies layer L1 to a new layer L2 in the target file.\n"
              << "              By default, saves in source_file_name if -o target_file_name is omitted.\n\n"
              << "  have_figure: ./processor source_file_name L1 have_figure\n"
              << "              Checks if layer L1 contains any figures.\n"
              << "              Returns 0 if figures are found, 1 otherwise.\n";
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        printUsage();
        return 1;
    }

    Processor processor;
    std::string source_file = argv[1];
    std::string command = argv[3];
    std::string target_file = source_file;  // default target is source file

    try {
        if (command == "unite" || command == "intersect" || command == "subtract") {
            if (argc < 8 || std::string(argv[5]) != "to") {
                printUsage();
                return 1;
            }
            
            std::string layer1 = argv[2];
            std::string layer2 = argv[4];
            std::string result_layer = argv[6];
            if (argc == 9 && std::string(argv[7]) == "-o") {
                target_file = argv[8];
            }
            
            if (command == "unite") {
                if (processor.uniteLayers(layer1, layer2, result_layer, source_file, target_file) != 0) return -1;
            } else if (command == "intersect") {
                if (processor.intersectLayers(layer1, layer2, result_layer, source_file, target_file) != 0) return -1;
            } else if (command == "subtract") {
                if (processor.subtractLayers(layer1, layer2, result_layer, source_file, target_file) != 0) return -1;
            }
        } else if (command == "expand" || command == "shrink") {
            if (argc < 8 || std::string(argv[5]) != "to") {
                printUsage();
                return 1;
            }

            std::string layer1 = argv[2];
            float size = std::stof(argv[4]);
            std::string result_layer = argv[6];
            if (argc == 9 && std::string(argv[7]) == "-o") {
                target_file = argv[8];
            }

            if (command == "expand") {
                if (processor.expandLayer(layer1, result_layer, size, source_file, target_file) != 0) return -1;
            } else if (command == "shrink") {
                if (processor.shrinkLayer(layer1, result_layer, size, source_file, target_file) != 0) return -1;
            }
        } else if (command == "del_layer") {
            if (argc != 4) {
                printUsage();
                return 1;
            }

            std::string layer_name = argv[2];
            if (processor.delLayer(layer_name, source_file) != 0) return -1;
        } else if (command == "rename_layer") {
            if (argc != 5) {
                printUsage();
                return 1;
            }

            std::string old_layer_name = argv[2];
            std::string new_layer_name = argv[4];
            if (processor.renameLayer(old_layer_name, new_layer_name, source_file) != 0) return -1;
        } else if (command == "copy_layer") {
            if (argc < 7 || std::string(argv[5]) != "to") {
                printUsage();
                return 1;
            }

            std::string layer1 = argv[2];
            std::string layer2 = argv[6];
            if (argc == 9 && std::string(argv[7]) == "-o") {
                target_file = argv[8];
            }

            if (processor.copyLayer(layer1, layer2, source_file, target_file) != 0) return -1;
        } else if (command == "have_figure") {
            if (argc != 4) {
                printUsage();
                return 1;
            }

            std::string layer_name = argv[2];
            int result = processor.layerHaveFigure(layer_name, source_file);
            return result ? 1 : 0;
        } else {
            printUsage();
            return 1;
        }
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
