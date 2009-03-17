/*
 *  Kula.cpp
 *  oxtorne
 *
 *  Created by Markus Friese on 16.03.09.
 *  Copyright 2009 Markus Friese. All rights reserved.
 *
 */

#include <vector>

#include "OxBox.h"

using namespace oxtorne;

std::vector<OxBox> objects;






int main(int argc, char* argv)
{
	objects.push_back(OxBox(make_box(0.0f, 0.0f, 0.0f, 0.5f)));
	objects.push_back(OxBox(make_box(1.0f, 0.0f, 0.0f, 0.5f)));
	objects.push_back(OxBox(make_box(2.0f, 0.0f, 0.0f, 0.5f)));
	objects.push_back(OxBox(make_box(3.0f, 1.0f, 0.0f, 0.5f)));
}
