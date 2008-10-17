
#ifndef OXVISUALIZE_H
#define OXVISUALIZE_H

#include <GL/glut.h>

#include "OxGeometry.h"
#include "OxMesh.h"

namespace oxtorne {

    template<typename T> GLuint wire (const box<T,3>&);
    template<typename T> GLuint wire (const line<T,3>&);
    template<typename T> GLuint wire (const ray<T,3>&);
    template<typename T> GLuint wire (const sphere<T,3>&);
    
    template<typename T> GLuint solid (mesh<T,3>&);
    template<typename T> GLuint solid (const point<T,3>&);
    template<typename T> GLuint solid (const sphere<T,3>&);
    
    template<typename T> void coordinate_system (const T&);

};

#if !defined(OXVISUALIZE_CPP)
#include "OxVisualize.cpp"
#endif

#endif
