/*
 *  OxBox.cpp
 *  oxtorne
 *
 *  Created by Markus Friese on 16.03.09.
 *  Copyright 2009 Markus Friese. All rights reserved.
 *
 */

#include "OxBox.h"
#include "OxGL.h"

OxBox::OxBox(const box<float,3>& _box)
{
    m_box = _box;
}

OxBox::~OxBox()
{
}

bool OxBox::collides(const OxObject& object) const
{
	return false;
}

bool OxBox::obstructing() const
{
	return true;
}

void OxBox::draw() const
{
    glColor3f(1.0f, 0.0f, 0.0f);
    oxtorne::draw_solid(m_box);
}
