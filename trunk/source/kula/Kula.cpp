/*
 *  Kula.cpp
 *  oxtorne
 *
 *  Created by Markus Friese on 16.03.09.
 *  Copyright 2009 Markus Friese. All rights reserved.
 *
 */

#include <vector>
#include <GLUT/glut.h>

#include "OxBox.h"

#include <stdio.h>

using namespace oxtorne;

std::vector<OxBox> objects;

float rota_x, rota_y;
float last_x, last_y;
float posi_x, posi_y, posi_z;

void world_display(void) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, 1.5, 1.0, 100.0);
    gluLookAt(posi_x, posi_y, posi_z, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);

    glPushMatrix();
    glRotatef(rota_x, 1.0, 0.0, 0.0);
    glRotatef(rota_y, 0.0, 1.0, 0.0);
    
    for (std::size_t i = 0; i < objects.size(); ++i)
        objects.at(i).draw();
        
    glPopMatrix();

    glutSwapBuffers();
}


void world_reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, 1.5, 1.0, 100.0);
    gluLookAt(-5.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
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
    rota_x += float(x - last_x);
    rota_y += float(y - last_y);
    
    last_x = float(x);
	last_y = float(y);

    printf("%i %i\n", x, y);

    glutPostRedisplay();
}


void world_keys(unsigned char key, int, int) {
    printf("%c\n", key);

    switch(key) {
        case 'w':
            posi_y += 0.5f;
            break;
        case 'x':
            posi_y -= 0.5f;
            break;
        case 'a':
            posi_x += 0.5f;
            break;
        case 'd':
            posi_x -= 0.5f;
            break;
        case 'q':
            posi_z += 0.5f;
            break;
        case 'e':
            posi_z -= 0.5f;
            break;
    }
    
    glutPostRedisplay();
}


int main(int argc, char* argv[])
{
    last_x = last_y = 0.0;
    rota_x = rota_y = 0.0;
    posi_x = -5.0;
    posi_y =  0.0;
    posi_z =  2.0;

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

	objects.push_back(OxBox(make_box(0.0f, 0.0f, 0.0f, 0.5f)));
	objects.push_back(OxBox(make_box(1.0f, 0.0f, 0.0f, 0.5f)));
	objects.push_back(OxBox(make_box(2.0f, 0.0f, 0.0f, 0.5f)));
	objects.push_back(OxBox(make_box(3.0f, 1.0f, 0.0f, 0.5f)));
    
    glutMainLoop();
}
