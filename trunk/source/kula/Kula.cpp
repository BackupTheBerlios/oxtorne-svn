/*
 *  Kula.cpp
 *  oxtorne
 *
 *  Created by Markus Friese on 16.03.09.
 *  Copyright 2009 Markus Friese. All rights reserved.
 *
 */
 
#include <vector>
#include <cmath>
#include <GLUT/glut.h>

#include "OxWorld.h"
#include "OxConsole.h"

#include <iostream>

using namespace oxtorne;
using std::cout;
using std::endl;

vector<float,3> forward;
vector<float,3> up;
point<float,3> position;

Player player;
World world(16, 12, 8);

float rota_x, rota_y;
float last_x, last_y;

void world_display(void) {
	

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.5, 1.0, 100.0);
    gluLookAt(
		  position[0]
		, position[1]
		, position[2]
		, position[0] + forward[0]
		, position[1] + forward[1]
		, position[2] + forward[2]
		, up[0]
		, up[1]
		, up[2]);

	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
	
	world.draw();
    player.draw();

    glutSwapBuffers();
}


void world_reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, 1.5, 1.0, 100.0);
    gluLookAt(-5.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	GLfloat light_position[] = { 1.0, 0.5, 0.75, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
}


void world_mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN)
        glutSetCursor(GLUT_CURSOR_INFO);
    else
        glutSetCursor(GLUT_CURSOR_LEFT_ARROW);

    last_x = x;
	last_y = y;
}


void world_motion(int x, int y) {
	
	vector<float,3> right = cross_product(up, forward);
	std::cout << "UP: " << up << std::endl;
	std::cout << "RIGHT:  " << right << std::endl;
	forward = normalize( rotate( right, forward,  float(y - last_y) / 100.0f ) );
	forward = normalize( rotate( up,    forward, -float(x - last_x) / 100.0f ) );
	up = normalize( cross_product(forward, right) );

	

    rota_x += float(x - last_x);
    rota_y += float(y - last_y);
    
    last_x = float(x);
	last_y = float(y);

    glutPostRedisplay();
}


void world_keys(unsigned char key, int, int) {
    printf("%c\n", key);

    switch(key) {
        case 'w':
            position = position + (forward * 0.6f);
            break;
        case 's':
            position = position - (forward * 0.6f);
            break;
        case 'a':
            position = position + (cross_product(up, forward) * 0.6f);
            break;
        case 'd':
            position = position - (cross_product(up, forward) * 0.6f);
            break;
        case 'u':
            player = world.move_forward(player);
            break;
        case 'k':
            player = world.rotate_left(player);
            break;
        case 'h':
            player = world.rotate_right(player);
            break;
    }
    
    glutPostRedisplay();
}


int main(int argc, char* argv[])
{
    forward = make_vector(1.0f, 0.0f, 0.0f);
    up      = make_vector(0.0f, 0.0f, 1.0f);
    position = make_point(5.0f, 0.0f, 0.0f);

    last_x = last_y = 0.0;
    rota_x = rota_y = 0.0;

	// ox_load_world_debug();

    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(512, 512);
    glutInitWindowPosition(8, 8);
    glutInit(&argc, argv);

    glutCreateWindow("Distances");
    glutReshapeFunc(world_reshape);
    glutDisplayFunc(world_display);
    glutMotionFunc(world_motion);
    glutMouseFunc(world_mouse);
    glutKeyboardFunc(world_keys);
    
    glutMainLoop();
}
