/*
 *  OxWorld.cpp
 *  oxtorne
 *
 *  Created by Markus Friese on 21.03.09.
 *  Copyright 2009 __MyCompanyName__. All rights reserved.
 *
 */

/// Common requirenments
//
#include "OxWorld.h"
#include "OxObject.h"


/// for debugging
//
#include "OxBox.h"


/// for ease of use
//
using namespace oxtorne;


/// World entities
//
static OxObject** objects;
static size_t n_objects;


/// Load world data for debugging
// return 0 on fail and 1 on success
//
int ox_load_world_debug( void ) {
	n_objects = 12;
	objects = (OxObject**) malloc (n_objects * sizeof(OxObject*));

	objects[0] = new OxBox(make_box(0.0f, 0.0f, 0.0f, 0.5f));
	objects[1] = new OxBox(make_box(1.0f, 0.0f, 0.0f, 0.5f));
	objects[2] = new OxBox(make_box(2.0f, 0.0f, 0.0f, 0.5f));
	objects[3] = new OxBox(make_box(3.0f, 1.0f, 0.0f, 0.5f));
	objects[4] = new OxBox(make_box(0.0f, 1.0f, 1.0f, 0.5f));
	objects[5] = new OxBox(make_box(1.0f, 1.0f, 1.0f, 0.5f));
	objects[6] = new OxBox(make_box(2.0f, 0.0f, 1.0f, 0.5f));
	objects[7] = new OxBox(make_box(3.0f, 1.0f, 2.0f, 0.5f));
	objects[8] = new OxBox(make_box(0.0f, 0.0f, 3.0f, 0.5f));
	objects[9] = new OxBox(make_box(1.0f, 0.0f, 4.0f, 0.5f));
	objects[10] = new OxBox(make_box(2.0f, 0.0f, 4.0f, 0.5f));
	objects[11] = new OxBox(make_box(3.0f, 1.0f, 4.0f, 0.5f));
	
	return 1;
}


/// Clear world data
// return 0 on fail and 1 on success
//
int ox_clear_world( void ) {
	free(objects);
	
	return 1;
}


/// Draw world data (however it's done)
// return 0 on fail and 1 on success
//
int ox_draw_world( void ) {
	
	for (size_t i = 0; i < n_objects; ++i)
		objects[i]->draw();
	
	return 1;
}

