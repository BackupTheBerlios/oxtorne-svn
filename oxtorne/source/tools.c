/*
 *  tools.c
 *  oxtorne tools library
 *
 */

#include "tools.h"

#include <stdio.h>
#include <OpenGL/gl.h>

int OX_v3d_print(const vector3d* _p) {
	return printf("(%f, %f, %f)\n", _p->x, _p->y, _p->z);
}

void OX_v3d_draw(const vector3d* _vector) {
    glVertex3d(
        _vector->x,
        _vector->y,
        _vector->z);
}

void OX_r3d_draw(const ray3d* _ray) {
    glVertex3d(
        _ray->origin.x,
        _ray->origin.y,
        _ray->origin.z);
    glVertex3d(
        _ray->origin.x + _ray->direction.x,
        _ray->origin.y + _ray->direction.y,
        _ray->origin.z + _ray->direction.z);
}
