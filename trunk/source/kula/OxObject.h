#ifndef OXOBJECT_INCLUDE
#define OXOBJECT_INCLUDE

/*
 *  OxObject.h
 *  oxtorne
 *
 *  Created by Markus Friese on 16.03.09.
 *  Copyright 2009 Markus Friese. All rights reserved.
 *
 */


class OxObject
{

public:
	
	virtual bool collides(const OxObject&) const = 0;
	virtual bool obstructing() const { return false; }
	virtual void draw() const = 0;

};

#endif
