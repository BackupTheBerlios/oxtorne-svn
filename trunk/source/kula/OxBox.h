/*
 *  OxBox.h
 *  oxtorne
 *
 *  Created by Markus Friese on 16.03.09.
 *  Copyright 2009 Markus Friese. All rights reserved.
 *
 */


#include "OxGeometry.h"
#include "OxObject.h"


using oxtorne::box;


class OxBox : public OxObject
{

public:
	OxBox(const box<float,3>&);
	~OxBox();
	
	bool collides(const OxObject&) const;
	bool obstructing() const;
	void draw() const;

protected:
    box<float,3> m_box;

};
