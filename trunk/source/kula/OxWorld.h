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
using namespace oxtorne;


// *****************************************************************************
class Player {

public:
    Player();
	Player( const point<float,3>&, const vector<float,3>&, const vector<float,3>& );
    virtual ~Player();
	void draw( void );

	// modifyable version
    inline vector<float,3>& forward() { return m_forward; }
    inline vector<float,3>& upward() { return m_upward; }
    inline point<float,3>& position() { return m_position; }

	// const version
	inline const vector<float,3>& forward() const { return m_forward; }
    inline const vector<float,3>& upward() const { return m_upward; }
    inline const point<float,3>& position() const { return m_position; }

protected:
    vector<float,3> m_forward;
    vector<float,3> m_upward;
    point<float,3> m_position;

};

// *****************************************************************************
class Block {

public:
    Block( const bool& = false );
    virtual ~Block();
	void draw( void );
    
    const bool& massive( void );

protected:
    bool m_massive;

};

// *****************************************************************************
class World {

public:
    World( const size_t&, const size_t&, const size_t& );
    virtual ~World();
    void draw( void );

	const size_t& size_x( void );
	const size_t& size_y( void );
	const size_t& size_z( void );
	Block& block_at( const int& x, const int& y, const int& z );

	bool above_solid( const Player& );
	bool facing_solid( const Player& );
	bool facing_abyss( const Player& );
	bool at_peak( const Player& );

	Player move_forward( const Player& );
	Player rotate_right( const Player& );
	Player rotate_left( const Player& );
	Player rotate_up( const Player& );
	Player rotate_down( const Player& );

protected:
    int x, y, z;
    std::vector<Block> field;
};

// *****************************************************************************
point<int,3> floor( const oxtorne::point<float,3>& );
point<int,3> ceil( const oxtorne::point<float,3>& );
vector<int,3> round( const oxtorne::vector<float,3>& );

#endif
