#include "wc.h"
#include <iostream>
#include <fstream>

int main(int argc, char* argv[]) {
    
    WcConfig config(argc, argv);
    
    std::vector<size_t> answers;

    if (config.filename.empty()) {
        answers = handle_queries(std::cin, config);
    } else {
        std::ifstream file(config.filename);
        answers = handle_queries(file, config);
    }

    // print answer
    for (const auto& num: answers)
        std::cout << " " << num;

    if (!config.filename.empty())
        std::cout << " " << config.filename;

    std::cout << "\n";
}
