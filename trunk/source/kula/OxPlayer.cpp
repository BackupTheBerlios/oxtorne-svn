/*
 *  OxPlayer.cpp
 *  oxtorne
 *
 *  Created by Markus Friese on 21.03.09.
 *  Copyright 2009 Markus Friese. All rights reserved.
 *
 */

#include "OxPlayer.h"
#include "OxGL.h"

using namespace oxtorne;


OxPlayer::OxPlayer()
{
    position = make_point(0.0f, 0.0f, 0.0f);
    forward = make_vector(1.0f, 0.0f, 0.0f);
    up = make_vector(0.0f, 0.0f, 1.0f);
}

OxPlayer::~OxPlayer()
{
    
}

void OxPlayer::draw( void )
{
    sphere<float,3> _sphere = make_sphere(position, 0.3f);
    draw_solid(_sphere);
}

void OxPlayer::go_forward( void )
{
    position = position + forward;
}

void OxPlayer::turn_left( void )
{
	forward = normalize( rotate( up, forward, 0.5f * 3.14159265f ) );
}

void OxPlayer::turn_right( void )
{
    forward = normalize( rotate( up, forward, -0.5f * 3.14159265f ) );
}

void OxPlayer::set_position( const point<float,3>& p )
{
    position = p;
}

void OxPlayer::set_forward( const vector<float,3>& f )
{
    forward = f;
}
    
void OxPlayer::set_up( const vector<float,3>& u )
{
    up = u;
}

const point<float,3>& OxPlayer::get_position( void )
{
    return position;
}
    
const vector<float,3>& OxPlayer::get_forward( void )
{
    return forward;
}
    
const vector<float,3>& OxPlayer::get_up( void )
{
    return up;
}




