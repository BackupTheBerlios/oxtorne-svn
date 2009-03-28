/**
 *******************************************************************************
 * <P> KulaGalaxy declaring Base types and functionality for the Kula
 * Galaxy Game. </P>
 *
 * @author      Markus S Friese
 *
 * @date		28. March 2009
 *******************************************************************************
 */


/*
 *******************************************************************************
 * Include only once
 *******************************************************************************
 */
#ifndef OXWORLD_INCLUDE
#define OXWORLD_INCLUDE

/*
 *******************************************************************************
 * Get all necessary headers
 *******************************************************************************
 */
#include "KulaMath.h"


/*
 *******************************************************************************
 * Structure used to represent a world coordinate system for the player
 *******************************************************************************
 */
typedef struct {
	kPoint3f position;
	kPoint3f forward;
	kPoint3f up;
} kPlayer;

/*
 *******************************************************************************
 * enum to represent type of block the player can stand on
 *******************************************************************************
 */
typedef enum {
	IMPALPABLE,
	SOLID
} kState;

/*
 *******************************************************************************
 * Structure to represent one Block, the basic entity in the game
 *******************************************************************************
 */
typedef struct {
	kState state;
} kBlock;

/*
 *******************************************************************************
 * Structure to represent the world
 *******************************************************************************
 */
typedef struct {
	kPoint3i size;
	kBlock** blocks;
} kWorld;

/*
 *******************************************************************************
 * Factoriies for world entities
 *******************************************************************************
 */
kPlayer make_player( const kPoint3f*, const kPoint3f*, const kPoint3f* );
kWorld make_world( const int, const int, const int );
kBlock make_block( void );

/*
 *******************************************************************************
 * Working with points here. transform them to integer points.
 *******************************************************************************
 */
kPoint3i floor3i( const kPoint3f* );
kPoint3i ceil3i( const kPoint3f* );
kPoint3i round3i( const kPoint3f* );

/*
 *******************************************************************************
 * Working with the world (and the player maybe) here.
 *******************************************************************************
 */
int is_above_solid( const kPlayer*, const kWorld* );
int is_facing_solid( const kPlayer*, const kWorld* );
int is_facing_abyss( const kPlayer*, const kWorld* );
int is_at_peak( const kPlayer*, const kWorld* );

/*
 *******************************************************************************
 * Do some interaction with the world
 *******************************************************************************
 */
kPlayer move_forward( const kPlayer*, const kWorld* );
kPlayer rotate_right( const kPlayer* );
kPlayer rotate_left( const kPlayer* );
kPlayer rotate_up( const kPlayer* );
kPlayer rotate_down( const kPlayer* );

/*
 *******************************************************************************
 * working with world properties
 *******************************************************************************
 */
kBlock* get_block_at( const kWorld*, const int, const int, const int );






/*


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


*/

#endif
