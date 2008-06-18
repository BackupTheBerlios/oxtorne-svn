/*
 *  tools.c
 *  oxtorne tools library
 *
 */

#include "tools.h"

#include <stdio.h>
#include <OpenGL/gl.h>

int OX3d_print(const vector3d* _p) {
	return printf("(%f, %f, %f)\n", _p->x, _p->y, _p->z);
}

void OX3d_draw_vector(const vector3d* _vector) {
    glVertex3d(
        _vector->x,
        _vector->y,
        _vector->z);
}
