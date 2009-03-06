
#include "OxMesh.h"
#include "OxTree.h"
#include "OxVisualize.h"

#include <GLUT/glut.h>

#include <iostream>
#include <cstdlib>
#include <vector>
#include <ctime>

static GLfloat translation_x = 0,  translation_y = 0;
static GLfloat rotation_x = 0,     rotation_y = 0;
static GLfloat last_x = 0,         last_y = 0;
static GLfloat zoom = 10;
static GLuint mouse_button;
static std::vector<GLuint> lists;

void world_display(void) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glOrtho(-zoom, zoom, -zoom, zoom, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(translation_x, translation_y, 0.0);
    glRotatef( rotation_y, 1.0, 0.0, 0.0);
	glRotatef(-rotation_x, 0.0, 0.0, 1.0);
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_LIGHTING);
    glEnable(GL_LIGHTING);
    glColor3f(1.0, 1.0, 1.0);

    glEnable(GL_COLOR_MATERIAL);

    for (std::size_t i = 0; i < lists.size(); i++)
        glCallList(lists[i]);

    glutSwapBuffers();
}


void world_reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glClearColor(1.0, 1.0, 1.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glOrtho(-zoom, zoom, -zoom, zoom, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
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

int main(int argc, char* argv[]) {
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
    glutFullScreen();

    typedef oxtorne::mesh<float,3> mesh;
    // typedef oxtorne::octree<float,3> tree;

    mesh _mesh;

    oxtorne::read_stl(_mesh, "./example/final.stl");
    //tree _tree = oxtorne::make_octree(_mesh, 5);
    //tree::node* _root = _tree.root();
    
    glColor3f(1.0f, 0.0f, 0.0f);

    //for (std::size_t i = 0; i < _root->size(); i++)
    //    lists.push_back(wire(_root->at(i)->value.first));

    GLuint mymesh = glGenLists(1);
    glNewList(mymesh, GL_COMPILE);
    glEnable(GL_LIGHTING);
    glColor3f(1.0f, 0.0f, 0.0f);
    glEnable(GL_NORMALIZE);

    glBegin(GL_TRIANGLES);
    /*for (mesh::fiter f_iter = _mesh.faces_begin(); f_iter != _mesh.faces_end(); ++f_iter) {
        mesh::f_handle _fhandle = *f_iter;
        oxtorne::vector<float,3> _v = _mesh.face_normal(_fhandle);
        glNormal3fv(&_v[0]);

        mesh::he_handle _he0 = _fhandle->edge;
        glVertex3f((*_he0->vertex)[0], (*_he0->vertex)[1], (*_he0->vertex)[2]); _he0 = _he0->next;
        glVertex3f((*_he0->vertex)[0], (*_he0->vertex)[1], (*_he0->vertex)[2]); _he0 = _he0->next;
        glVertex3f((*_he0->vertex)[0], (*_he0->vertex)[1], (*_he0->vertex)[2]);
    }*/

    /*for (std::size_t i = 0; i < _root->at(2)->at(4)->value.second.size(); ++i) {
        mesh::f_handle _fhandle = _root->at(2)->at(4)->value.second[i];

        oxtorne::vector<float,3> _v = _mesh.face_normal(_fhandle);
        glNormal3fv(&_v[0]);

        mesh::he_handle _he0 = _fhandle->edge;
        glVertex3f((*_he0->vertex)[0], (*_he0->vertex)[1], (*_he0->vertex)[2]); _he0 = _he0->next;
        glVertex3f((*_he0->vertex)[0], (*_he0->vertex)[1], (*_he0->vertex)[2]); _he0 = _he0->next;
        glVertex3f((*_he0->vertex)[0], (*_he0->vertex)[1], (*_he0->vertex)[2]);
    }*/

    glEnd();
    glEndList();

    lists.push_back(mymesh);
    
    glutMainLoop();

    // system("PAUSE");
}
