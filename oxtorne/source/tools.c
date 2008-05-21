/*
 *  tools.c
 *  oxtorne tools library
 *
 */

#include "tools.h"

#include <stdio.h>

int OX_v2d_print(const vector2d* _p) {
	return printf("(%f, %f)\n", _p->x, _p->y);
}

int OX_v3d_print(const vector3d* _p) {
	return printf("(%f, %f, %f)\n", _p->x, _p->y, _p->z);
}
