
#include "OxTree.h"

#include <iostream>

int main(int argc, char* argv) {
    node<int,2> _node;
    
    std::cout << _node.value << std::endl;
    std::cout << _node.size() << std::endl;
    
    node<int,2>::iterator n_iter = _node.begin();
    node<int,2>::iterator n_end  = _node.end();
    
    _node.value = 42;
    _node.assign(0, 16);
    _node.assign(1, 32);
    
    
    for (; n_iter != n_end; n_iter++) {
        std::cout << "by iterator " << n_iter->value << std::endl;
    }
    
    for (int i = 0; i < _node.size(); ++i) {
        std::cout << "by index " << _node[i]->value << std::endl;
    }
}
