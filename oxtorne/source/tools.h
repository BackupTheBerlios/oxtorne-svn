/*
 *  tools.h
 *  oxtorne tools library
 *
 */

#ifndef TOOLS_H
#define TOOLS_H

#include "geometry.h"

int 
    OX_v3d_print(const vector3d*);

void
    OX_v3d_draw(const vector3d*),
    OX_r3d_draw(const ray3d*);

#endif
