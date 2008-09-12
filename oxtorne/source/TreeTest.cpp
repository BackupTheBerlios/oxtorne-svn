
#include "OxTree.h"

#include <iostream>

int main(int argc, char* argv) {
    node<int,2> _node;
    
    std::cout << _node.value << std::endl;
    std::cout << _node.size() << std::endl;
    
    node<int,2>::iterator n_iter = _node.begin();
    node<int,2>::iterator n_end  = _node.end();
    
    for (; n_iter != n_end; n_iter++) {
        std::cout << *n_iter << std::endl;
    }
}
