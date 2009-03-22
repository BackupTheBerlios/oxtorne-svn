#ifndef OXPLAYER_INCLUDE
#define OXPLAYER_INCLUDE

/*
 *  OxPlayer.h
 *  oxtorne
 *
 *  Created by Markus Friese on 21.03.09.
 *  Copyright 2009 Markus Friese. All rights reserved.
 *
 */

#include "OxGeometry.h"


class OxPlayer 
{

public:
    OxPlayer();
    ~OxPlayer();
    
    void draw( void );

    void go_forward( void );
    void turn_left( void );
    void turn_right( void );
    
    void set_position( const oxtorne::point<float,3>& );
    void set_forward( const oxtorne::vector<float,3>& );
    void set_up( const oxtorne::vector<float,3>& );

    const oxtorne::point<float,3>& get_position( void );
    const oxtorne::vector<float,3>& get_forward( void );
    const oxtorne::vector<float,3>& get_up( void );

protected:
    oxtorne::point<float,3> position;
    oxtorne::vector<float,3> forward;
    oxtorne::vector<float,3> up;

};


#endif
