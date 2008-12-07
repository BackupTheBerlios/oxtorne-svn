/*
 *  Pong.cpp
 *  oxtorne
 *
 *  Created by Markus F on 07.12.08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "OxGeometry.h"
#include "OxVisualize.h"

#include <GLUT/glut.h>

#include <iostream>

using namespace oxtorne;

struct player {
    vector<float,3> movement;
    point<float,3> position;
    float size;
};

struct pucky {
    vector<float,3> movement;
    point<float,3> position;
    float radius;
    float speed;
};

struct playground {
    float height;
    float width;
};

static player player_1;
static player player_2;
static pucky ball;
static playground field;

static int last_x, last_y;

void draw_player(const player& p) {
    glPushMatrix();
    glTranslatef(p.position[0], p.position[1], p.position[2]);
    glutWireSphere(p.size, 16, 16);
    glPopMatrix();
}

void draw_puck(const pucky& p) {
    glPushMatrix();
    glTranslatef(p.position[0], p.position[1], p.position[2]);
    glutWireSphere(p.radius, 16, 16);
    glPopMatrix();
}

void draw_playground(const playground& p) {
    glBegin(GL_LINE_STRIP);
    glVertex3f(-p.width,  p.height, 0.0f);
    glVertex3f( p.width,  p.height, 0.0f);
    glVertex3f( p.width, -p.height, 0.0f);
    glVertex3f(-p.width, -p.height, 0.0f);
    glVertex3f(-p.width,  p.height, 0.0f);
    glEnd();
}

void ball_playground(const playground& pg, pucky& b) {
    if (b.position[0] < -pg.width) {
        b.position[0] = -pg.width;
        b.movement[0] = b.movement[0] * -1.0f;
    } else if (b.position[1] < -pg.height) {
        b.position[1] = -pg.height;
        b.movement[1] = b.movement[1] * -1.0f;
    } else if (b.position[0] > pg.width) {
        b.position[0] = pg.width;
        b.movement[0] = b.movement[0] * -1.0f;
    } else if (b.position[1] > pg.height) {
        b.position[1] = pg.height;
        b.movement[1] = b.movement[1] * -1.0f;
    }
}

void player_playground(const playground& pg, player& p) {
    if (p.position[0] < -pg.width) {
        p.position[0] = -pg.width;
    } else if (p.position[0] > pg.width) {
        p.position[0] = pg.width;
    }
    
    if (p.position[1] < -pg.height) {
        p.position[1] = -pg.height;
    } else if (p.position[1] > pg.height) {
        p.position[1] = pg.height;
    }
}

void ball_player(const player& p, pucky& b) {
    float dist = distance(p.position, b.position);
    float distmin = p.size + b.radius;

    if (dist > distmin)
        return;
        
    b.speed = b.speed + length(p.movement);
    
    vector<float,3> cutvec = normalize(b.position - p.position);
    point<float,3> cutpos = p.position + (cutvec * p.size);
    plane<float,3> cutplane = make_plane(cutpos, cutvec);

    b.movement = normalize(mirror(cutplane, b.movement));
    
    if (dot_product(b.movement, cutvec) < 0.0f) {
        std::cout << "ERROR!!" << std::endl;
    }
}

void ball_movement(pucky& b) {
    b.speed = b.speed * 0.998f;
    if (b.speed < 0.05f)
        b.speed = 0.05f;
    else if (b.speed > 1.0f)
        b.speed = 1.0f;
    b.position = b.position + (normalize(b.movement) * b.speed);
    
}

void world_display(void) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glFrustum(-field.width, field.width, -field.height, field.height, 45.0f, 55.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_COLOR_MATERIAL);

    glTranslated(-0.0f, -0.0f, -50.0f);
    glRotatef(90, 0.0, 0.0, 1.0);
    
    glColor3f(0.0f, 0.0f, 0.0f);
    
    draw_player(player_1);
    // draw_player(player_2);
    draw_playground(field);
    draw_puck(ball);
    
    glutSwapBuffers();
}


void world_reshape(int width, int height) {
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glFrustum(-field.width, field.width, -field.height, field.height, 45.0f, 55.0f);
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void key_pressed(unsigned char key, int x, int y) {
    if (key == 'q')
        exit(0);
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
    vector<float,3> m = make_vector(float(last_y - y), float(last_x - x), 0.0f);
    m = m * 0.01f;
    
    player_1.movement = player_1.movement + m;
    
    last_x = x;
    last_y = y;
}


void world_time(int value) {
    glutTimerFunc(10, world_time, 0);
    
    player_1.position = player_1.position + player_1.movement;
    player_1.movement = player_1.movement * 0.9f;
    
    ball_movement(ball);
    
    player_playground(field, player_1);
    ball_playground(field, ball);
    ball_player(player_1, ball);
    
    
    glutPostRedisplay();
}

int main(int argc, char* argv[]) {

    player_1.movement = make_vector(0.0f, 0.0f, 0.0f);
    player_2.movement = make_vector(0.0f, 0.0f, 0.0f);
    player_1.position = make_point(0.0f, 5.0f, 0.0f);
    player_2.position = make_point(0.0f, 0.0f, 0.0f);
    player_1.size = 3.0f;
    player_2.size = 3.0f;
    
    ball.movement = make_vector(0.1f, 0.1f, 0.0f);
    ball.position = make_point(0.0f, 0.0f, 0.0f);
    ball.radius = 2.0f;
    ball.speed = 0.0f;
    
    field.width = 15.0f;
    field.height = 15.0f;
    
    last_x = last_y = 0;

    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(512, 512);
    glutInitWindowPosition(50, 50);
    glutInit(&argc, argv);

    glutCreateWindow("Distances");
    glutReshapeFunc(world_reshape);
    glutDisplayFunc(world_display);
    glutMotionFunc(world_motion);
    glutMouseFunc(world_mouse);
    glutKeyboardFunc(key_pressed);
    glutTimerFunc(10, world_time, 0);
    // glutFullScreen();

    
    glutMainLoop();
}
