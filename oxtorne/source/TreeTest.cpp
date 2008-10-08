
#include "OxMesh.h"

#include <iostream>

int main(int argc, char* argv) {

    typedef oxtorne::mesh<int,3> mesh;

    mesh _mesh;

    _mesh.add_vertex(oxtorne::make_point(4, 3, 4));
    _mesh.add_vertex(oxtorne::make_point(2, 1, 7));
    _mesh.add_vertex(oxtorne::make_point(3, 5, 4));
    
    _mesh.add_face(_v0, _v1, _v2);

    system("PAUSE");
}
