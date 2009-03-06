
#include <iostream>

#include "OxMemory.h"

int main(int argc, char* argv[]) {
    array<int> _array;
    
    for (size_t i = 0; i < 100000; ++i) {
        _array.push_back(i);
        std::cout << i << std::endl;
    }

    std::cout << "OKAY" << std::endl;
    _array.clear();
    std::cout << "OKAY" << std::endl;
    system("sleep 16");
}
