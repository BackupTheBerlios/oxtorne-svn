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
#include "OxGL.h"
#include <cmath>

using namespace oxtorne;

// *****************************************************************************
Player::Player()
{
    forward = make_vector(1.0f, 0.0f, 0.0f);
    upward = make_vector(0.0f, 0.0f, 1.0f);
    position = make_point(0.5f, 0.5f, 1.5f);
}

Player::~Player()
{
}

oxtorne::vector<float,3>& Player::get_forward() { return forward; }
oxtorne::vector<float,3>& Player::get_upward() { return upward; }
oxtorne::point<float,3>& Player::get_position() { return position; }

void Player::draw( void )
{
    sphere<float,3> _sphere = make_sphere(position, 0.3f);
    draw_solid(_sphere);
}

void Player::move_forward( void ) {
    position = position + forward;
}

void Player::rotate_right( void ) {
    forward = normalize( rotate( upward, forward, -0.5f * 3.14159265f ) );
}

void Player::rotate_left( void ) {
    forward = normalize( rotate( upward, forward, 0.5f * 3.14159265f ) );
}

// *****************************************************************************
Block::Block( const bool& m )
{
    massive = m;
}

Block::~Block()
{
}
    
void Block::set_massive( const bool& m )
{
    massive = m;
}

bool Block::is_massive( void )
{
    return massive;
}

void Block::draw( void )
{
    // always draw between 0 and 1
    draw_solid( make_box(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f) );
}

// *****************************************************************************
World::World( const int& x, const int& y, const int& z, bool debug )
{
    size_x = x;
    size_y = y;
    size_z = z;

    gameField.assign(x * y * z, Block());
    
    if (debug)
    {
        set_block_at(0, 0, 0, Block(true));
        set_block_at(1, 0, 0, Block(true));
        set_block_at(2, 0, 0, Block(true));
        set_block_at(3, 0, 0, Block(true));
        set_block_at(3, 0, 1, Block(true));
    }
}

World::~World()
{
}

bool World::above_solid( Player& player )
{
    // meaning the negative up direction points towards a solid block
    point<int,3> position = floor( player.get_position() );
    vector<int,3> up = round( player.get_upward() );
    // the floor is now at the position - up direction
    point<int,3> floor = position - up;
    
    // now simply check, if the floor is set to solid
    return get_block_at(floor[0], floor[1], floor[2]).is_massive();
}

bool World::facing_solid( Player& player )
{
    // meaning the negative forward direction points towards a solid block
    point<int,3> position = floor( player.get_position() );
    vector<int,3> forward = round( player.get_forward() );
    // the floor is now at the position - up direction
    point<int,3> wall = position + forward;
    
    // now simply check, if the floor is set to solid
    return get_block_at(wall[0], wall[1], wall[2]).is_massive();
}

void World::set_block_at( const int& x, const int& y, const int& z, const Block& block )
{
    // Faelle ausschliessen
    if (x < 0 || x >= size_x) return;
    if (y < 0 || y >= size_y) return;
    if (z < 0 || z >= size_z) return;
    
    gameField.at(z * (size_x * size_y) + y * size_x + x) = block;
}

Block World::get_block_at( const int& x, const int& y, const int& z )
{
    // Faelle ausschliessen
    if (x < 0 || x >= size_x) return Block();
    if (y < 0 || y >= size_y) return Block();
    if (z < 0 || z >= size_z) return Block();
    
    return gameField.at(z * (size_x * size_y) + y * size_x + x);
}

void World::draw( void )
{
    for (size_t x = 0; x < size_x; ++x)
        for (size_t y = 0; y < size_y; ++y)
            for (size_t z = 0; z < size_z; ++z)
            {
                // do we have to draw?
                if ( get_block_at(x, y, z).is_massive() )
                {
                    glPushMatrix();
                    glTranslatef(float(x), float(y), float(z));
                    get_block_at(x, y, z).draw();
                    glPopMatrix();
                }
            }
}

// *****************************************************************************
point<int,3> floor( const point<float,3>& _point )
{
    return make_point(
        int(floor( _point[0] )),
        int(floor( _point[1] )),
        int(floor( _point[2] )));
}

point<int,3> ceil( const point<float,3>& _point )
{
    return make_point(
        int(ceil( _point[0] )),
        int(ceil( _point[1] )),
        int(ceil( _point[2] )));
}

vector<int,3> round( const vector<float,3>& _vector )
{
    return make_vector(
        int(floor( _vector[0] + 0.5f )),
        int(floor( _vector[1] + 0.5f )),
        int(floor( _vector[2] + 0.5f )));
}
