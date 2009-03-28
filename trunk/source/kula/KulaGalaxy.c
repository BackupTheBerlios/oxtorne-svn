/**
 *******************************************************************************
 * <P> KulaGalaxy.c containing base world information. </P>
 *
 * @author      Markus S Friese
 *
 * @date		28. March 2009
 *******************************************************************************
 */


/*
 *******************************************************************************
 * Include all necessary include files
 *******************************************************************************
 */
#include "KulaGalaxy.h"

#include <stdlib.h>
#include <math.h>


/*
 *******************************************************************************
 * Implementation of the player factory
 *******************************************************************************
 */
kPlayer make_player( const kPoint3f* position, const kPoint3f* forward, const kPoint3f* up )
{
	kPlayer player;
	player.position = *position;
	player.forward = *forward;
	player.up = *up;
	return player;
}


/*
 *******************************************************************************
 * Factoriy for the world. The level content will be created on the heap space.
 * The world will be empty.
 *******************************************************************************
 */
kWorld make_world( const int x, const int y, const int z )
{
	kWorld world;
	world.size = make_point3i(x, y, z);
	world.blocks = (kBlock**) malloc( (x * y * z + 1) * sizeof( kBlock* ) );
	
	int i;
	for (i = 0; i < x * y * z; ++i)
	{
		world.blocks[i] = (kBlock*) malloc( sizeof( kBlock ) );
		*world.blocks[i] = make_block();
	}
	
	return world;
}

/*
 *******************************************************************************
 * modify the point to get an integer point by taking the floor argument
 *******************************************************************************
 */
kBlock make_block( void )
{
	kBlock block;
	block.state = IMPALPABLE;
	return block;
}

/*
 *******************************************************************************
 * modify the point to get an integer point by taking the floor argument
 *******************************************************************************
 */
kPoint3i floor3i( const kPoint3f* p )
{
	return make_point3i(
		(int) floor(p->x),
		(int) floor(p->y),
		(int) floor(p->z)
	);
}

/*
 *******************************************************************************
 * modify the point to get an integer point by taking the ceil argument
 *******************************************************************************
 */
kPoint3i ceil3i( const kPoint3f* p )
{
	return make_point3i(
		(int) ceil(p->x),
		(int) ceil(p->y),
		(int) ceil(p->z)
	);
}


/*
 *******************************************************************************
 * round each coordinate to the next integer value
 *******************************************************************************
 */
kPoint3i round3i( const kPoint3f* p )
{
	return make_point3i(
		(int) floor(p->x) + 0.5f,
		(int) floor(p->y) + 0.5f,
		(int) floor(p->z) + 0.5f
	);
}

/*
 *******************************************************************************
 * Check out, if the player is above something he can stand on
 *******************************************************************************
 */
int is_above_solid( const kPlayer* player, const kWorld* world )
{
    kPoint3i position = floor3i( &player->position );
    kPoint3i up = round3i( &player->up );
    kPoint3i floor = minus3i( &position, &up );
    
    // now simply check, if the floor is set to solid
    return get_block_at(world, floor.x, floor.y, floor.z)->state != IMPALPABLE;
}

/*
 *******************************************************************************
 * Check out, if the player is facing a solid which cannot be passed
 *******************************************************************************
 */
int is_facing_solid( const kPlayer* player, const kWorld* world )
{
	// meaning the negative forward direction points towards a solid block
    kPoint3i position = floor3i( &player->position );
    kPoint3i forward = round3i( &player->forward );
    // the floor is now at the position - up direction
    kPoint3i wall = plus3i( &position, &forward );
    
    // now simply check, if the floor is set to solid
    return get_block_at(world, wall.x, wall.y, wall.z)->state != IMPALPABLE;
}

/*
 *******************************************************************************
 * Check out, if the player is facing an abyss
 *******************************************************************************
 */
int is_facing_abyss( const kPlayer* player, const kWorld* world )
{
	// meaning the negative forward direction points towards a solid block
    kPoint3i position = floor3i( &player->position );
    kPoint3i forward = round3i( &player->forward );
	kPoint3i up = round3i( &player->up );
    // the floor is now at the position - up direction
	position = plus3i( &position, &forward );
    kPoint3i wall = minus3i( &position, &up);
    
    // now simply check, if the floor is set to solid
    return get_block_at(world, wall.x, wall.y, wall.z)->state != IMPALPABLE;
}

/*
 *******************************************************************************
 * Check out, if the player is at a peak, which enables changing the side
 *******************************************************************************
 */
int is_at_peak( const kPlayer* player, const kWorld* world )
{
	return 1;
}

/*
 *******************************************************************************
 * Check out, if the player is at a peak, which enables changing the side
 *******************************************************************************
 */
kPlayer move_forward( const kPlayer*, const kWorld* );

/*
 *******************************************************************************
 * rotate the player by the vertical axis by the given degree
 *******************************************************************************
 */
kPlayer rotate( const kPlayer* player )
{
	vector<float,3> forward = normalize( rotate( player.upward(), player.forward(), 0.5f * 3.14159265f ) );
	return Player( player.position(), player.upward(), forward );
}

/*
 *******************************************************************************
 * Check out, if the player is at a peak, which enables changing the side
 *******************************************************************************
 */
kPlayer rotate_left( const kPlayer* );

/*
 *******************************************************************************
 * Check out, if the player is at a peak, which enables changing the side
 *******************************************************************************
 */
kPlayer rotate_up( const kPlayer* );

/*
 *******************************************************************************
 * Check out, if the player is at a peak, which enables changing the side
 *******************************************************************************
 */
kPlayer rotate_down( const kPlayer* );

/*
 *******************************************************************************
 * Get a block from the world. blocks out of range will be non solid.
 *******************************************************************************
 */
kBlock* get_block_at( const kWorld* world, const int x, const int y, const int z )
{
	// the last element is a stub
	if ( x < 0 || world->size.x >= x )
		{ return world->blocks[world->size.x * world->size.y * world->size.z + 1]; }
	if ( y < 0 || world->size.y >= y )
		{ return world->blocks[world->size.x * world->size.y * world->size.z + 1]; }
	if ( z < 0 || world->size.z >= z )
		{ return world->blocks[world->size.x * world->size.y * world->size.z + 1]; }
	
	// we are now for sure in range
	return world->blocks[(world->size.x + world->size.y) * z + world->size.x * y + x];
}

/*

/// Common requirenments
//
#include "OxConsole.h"
#include "OxWorld.h"
#include "OxGL.h"
#include <cmath>

// *****************************************************************************
Player::Player()
{
    forward() = make_vector(1.0f, 0.0f, 0.0f);
    upward() = make_vector(0.0f, 0.0f, 1.0f);
    position() = make_point(0.5f, 0.5f, 1.5f);
}

Player::Player( const point<float,3>& position
			  , const vector<float,3>& upward
			  , const vector<float,3>& forward )
			  : m_position( position )
			  , m_upward( upward )
			  , m_forward( forward )
{
}

Player::~Player()
{
}

void Player::draw( void )
{
    sphere<float,3> _sphere = make_sphere( position(), 0.2f );
    draw_solid(_sphere);
	
	glBegin(GL_LINES);
	glEnable(GL_COLOR_MATERIAL);
	glColor3d(0.0, 1.0, 0.0);
	glVertex3fv(&position()[0]);
	glVertex3fv(&(position() + forward())[0]);
	glColor3d(0.0, 0.0, 1.0);
	glVertex3fv(&position()[0]);
	glVertex3fv(&(position() + upward())[0]);
	glEnd();
}

// *****************************************************************************
Block::Block( const bool& m )
{
    m_massive = m;
}

Block::~Block()
{
}

const bool& Block::massive( void )
{
    return m_massive;
}

void Block::draw( void )
{
    // always draw between 0 and 1
    draw_solid( make_box(0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f) );
}

// *****************************************************************************
World::World( const size_t& _x, const size_t& _y, const size_t& _z )
{
    x = _x;
    y = _y;
    z = _z;

	// the last one is a stub
    field.assign( x * y * z + 1, Block() );
    
    block_at( 0, 0, 0 ) = Block( true );
    block_at( 1, 0, 0 ) = Block( true );
    block_at( 2, 0, 0 ) = Block( true );
    block_at( 3, 0, 0 ) = Block( true );
    block_at( 3, 0, 1 ) = Block( true );
}

World::~World()
{
}

Block& World::block_at( const int& _x, const int& _y, const int& _z )
{
    // Faelle ausschliessen
    if (_x < 0 || _x >= x) return field.back();
    if (_y < 0 || _y >= y) return field.back();
    if (_z < 0 || _z >= z) return field.back();
    
    return field.at(_z * (x * y) + _y * x + _x);
}


void World::draw( void )
{
    for (size_t _x = 0; _x < x; ++_x)
        for (size_t _y = 0; _y < y; ++_y)
            for (size_t _z = 0; _z < z; ++_z)
            {
                // do we have to draw?
                if ( block_at(_x, _y, _z).massive() )
                {
                    glPushMatrix();
                    glTranslatef(float(_x), float(_y), float(_z));
                    block_at(_x, _y, _z).draw();
                    glPopMatrix();
                }
            }
}

bool World::above_solid( const Player& player )
{
    // meaning the negative up direction points towards a solid block
    point<int,3> position = floor( player.position() );
    vector<int,3> up = round( player.upward() );
    // the floor is now at the position - up direction
    point<int,3> floor = position - up;
    
    // now simply check, if the floor is set to solid
    return block_at(floor[0], floor[1], floor[2]).massive();
}

bool World::facing_solid( const Player& player )
{
    // meaning the negative forward direction points towards a solid block
    point<int,3> position = floor( player.position() );
    vector<int,3> forward = round( player.forward() );
    // the floor is now at the position - up direction
    point<int,3> wall = position + forward;
    
    // now simply check, if the floor is set to solid
    return block_at(wall[0], wall[1], wall[2]).massive();
}

bool World::facing_abyss( const Player& player )
{
	// one forward and one down might be an abyss
	point<int,3> position = floor( player.position() );
    vector<int,3> forward = round( player.forward() );
	vector<int,3> up = round( player.upward() );
    // the floor is now at the position - up direction
    point<int,3> abyss = position + forward - up;
	
	// now simply check, if the floor is set to solid
	return !block_at(abyss[0], abyss[1], abyss[2]).massive();
}

bool World::at_peak( const Player& player )
{
	return true;
}

Player World::move_forward( const Player& player )
{
	if ( facing_solid( player ) )
	{
		// block ahead, we rotate upwards
		return rotate_up( player );
	}
	
	if ( facing_abyss( player ) )
	{
		// abyss ahed, we rotate down (if)
		return rotate_down( Player( player.position() + player.forward() - player.upward(), player.upward(), player.forward() ) );
	}

    point<float,3> position = player.position() + player.forward();
	return Player( position, player.upward(), player.forward() );
}

Player World::rotate_right( const Player& player )
{
    vector<float,3> forward = normalize( rotate( player.upward(), player.forward(), 0.5f * 3.14159265f ) );
	return Player( player.position(), player.upward(), forward );
}

Player World::rotate_left( const Player& player )
{
    vector<float,3> forward = normalize( rotate( player.upward(), player.forward(), -0.5f * 3.14159265f ) );
	return Player( player.position(), player.upward(), forward );
}

Player World::rotate_up( const Player& player )
{
	vector<float,3> right = normalize( cross_product( player.upward(), player.forward() ) );
	vector<float,3> forward = rotate( right, player.forward(), -0.5f * 3.14159265f );
	vector<float,3> up = rotate( right, player.upward(), -0.5f * 3.14159265f );
	return Player( player.position(), up, forward );
}

Player World::rotate_down( const Player& player ) {
	vector<float,3> right = normalize( cross_product( player.upward(), player.forward() ) );
	vector<float,3> forward = rotate( right, player.forward(), 0.5f * 3.14159265f );
	vector<float,3> up = rotate( right, player.upward(), 0.5f * 3.14159265f );
	return Player( player.position(), up, forward );
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

*/

