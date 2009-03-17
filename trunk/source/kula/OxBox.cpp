/*
 *  OxBox.cpp
 *  oxtorne
 *
 *  Created by Markus Friese on 16.03.09.
 *  Copyright 2009 Markus Friese. All rights reserved.
 *
 */

#include "OxBox.h"

OxBox::OxBox(const box<float,3>&)
{
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
}
