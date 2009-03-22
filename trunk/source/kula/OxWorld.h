#ifndef OXWORLD_INCLUDE
#define OXWORLD_INCLUDE

/*
 *  OxWorld.h
 *  oxtorne
 *
 *  Created by Markus Friese on 21.03.09.
 *  Copyright 2009 Markus Friese. All rights reserved.
 *
 */

#include <vector>

#include "OxGeometry.h"

class Player {

public:
    Player();
    virtual ~Player();

    oxtorne::vector<float,3>& get_forward();
    oxtorne::vector<float,3>& get_upward();
    oxtorne::point<float,3>& get_position();

    void draw( void );
    
    void move_forward( void );
    void rotate_right( void );
    void rotate_left( void );

protected:
    oxtorne::vector<float,3> forward;
    oxtorne::vector<float,3> upward;
    oxtorne::point<float,3> position;

};

// *****************************************************************************
class Block {

public:
    Block( const bool& = false);
    virtual ~Block();
    
    void set_massive( const bool& );
    bool is_massive( void );
    
    void draw( void );

protected:
    bool massive;

};

// *****************************************************************************
class World {

public:
    World( const int& x, const int& y, const int& z, bool = true);
    virtual ~World();

    bool above_solid( Player& );
    bool facing_solid( Player& );
    
    void draw( void );

protected:

    void set_block_at( const int& x, const int& y, const int& z, const Block& );
    Block get_block_at( const int& x, const int& y, const int& z );

    int size_x, size_y, size_z;
    std::vector<Block> gameField;
};

// *****************************************************************************
oxtorne::point<int,3> floor( const oxtorne::point<float,3>& );
oxtorne::point<int,3> ceil( const oxtorne::point<float,3>& );
oxtorne::vector<int,3> round( const oxtorne::vector<float,3>& );

#endif
