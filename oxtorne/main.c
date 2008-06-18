
#include "GLUT/glut.h"
#include "stdio.h"

#include "tools.h"

static GLfloat translation_x = 0,  translation_y = 0;
static GLfloat rotation_x = 90,    rotation_y = 0;
static GLfloat last_x = 0,         last_y = 0;
static GLfloat zoom = 10;
static GLuint mouse_button;

void world_display(void) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glOrtho(-zoom, zoom, -zoom, zoom, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(translation_x, translation_y, 0.0);
    glRotatef( rotation_y, 1.0, 0.0, 0.0);
	glRotatef(-rotation_x, 0.0, 0.0, 1.0);
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glutSwapBuffers();
}

void world_reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glOrtho(-zoom, zoom, -zoom, zoom, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	glEnable(GL_DEPTH_TEST);
}

void world_mouse(int button, int state, int x, int y) {
    if (state == GLUT_DOWN)
        glutSetCursor(GLUT_CURSOR_INFO);
    else
        glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
    
    mouse_button = button;
    last_x = x;
	last_y = y;
}

void world_motion(int x, int y) {
    if (mouse_button == GLUT_LEFT_BUTTON) {
        translation_x += (GLfloat) -(last_x - x) / 20.0;
		translation_y += (GLfloat)  (last_y - y) / 20.0;
    } else if (mouse_button == GLUT_RIGHT_BUTTON) {
		rotation_x += (GLfloat)  (last_x - x) / 2.0;
		rotation_y -= (GLfloat)  (last_y - y) / 2.0;
	} else if (mouse_button == GLUT_MIDDLE_BUTTON) {
		zoom += (GLfloat) (last_y - y) / 10.0;
		if (zoom < 0.1) zoom = 0.1;
	}
	
	last_x = x;
	last_y = y;

    glutPostRedisplay();
}

void menu_callbacks(int selection) {
    switch (selection) {
        case 'x':
            printf("You wanna clear\n");
            break;
        case 'q':
            printf("You wanna exit\n");
            break;
    }
}

int main (int argc, char** argv) {
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition(50, 50);
    glutInit(&argc, argv);
 
    glutCreateWindow("Distances");
    glutReshapeFunc(world_reshape);
    glutDisplayFunc(world_display);
    glutMotionFunc(world_motion);
    glutMouseFunc(world_mouse);
    
    glutCreateMenu(menu_callbacks);
    glutAddMenuEntry("Clear", 'x');
    glutAddMenuEntry("Quit", 'q');
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    
    glutMainLoop();
    return 0;
}
