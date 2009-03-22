
#include "OxGeometry.h"
#include <OpenGL/gl.h>
#include <GLUT/glut.h>

namespace oxtorne {

template<typename T> inline
void draw_solid(const oxtorne::box<T, 3>& _box) {

    
    glBegin(GL_QUADS);
        glNormal3f(0.0f, 0.0f, -1.0f);
        glVertex3f(_box.min[0], _box.min[1], _box.min[2]);
        glVertex3f(_box.max[0], _box.min[1], _box.min[2]);
        glVertex3f(_box.max[0], _box.max[1], _box.min[2]);
        glVertex3f(_box.min[0], _box.max[1], _box.min[2]);
        
        glNormal3f(0.0f, 0.0f, 1.0f);
        glVertex3f(_box.min[0], _box.min[1], _box.max[2]);
        glVertex3f(_box.max[0], _box.min[1], _box.max[2]);
        glVertex3f(_box.max[0], _box.max[1], _box.max[2]);
        glVertex3f(_box.min[0], _box.max[1], _box.max[2]);
        
        glNormal3f(-1.0f, 0.0f, 0.0f);
        glVertex3f(_box.min[0], _box.min[1], _box.min[2]);
        glVertex3f(_box.min[0], _box.max[1], _box.min[2]);
        glVertex3f(_box.min[0], _box.max[1], _box.max[2]);
        glVertex3f(_box.min[0], _box.min[1], _box.max[2]);
        
        glNormal3f(1.0f, 0.0f, 0.0f);
        glVertex3f(_box.max[0], _box.min[1], _box.min[2]);
        glVertex3f(_box.max[0], _box.max[1], _box.min[2]);
        glVertex3f(_box.max[0], _box.max[1], _box.max[2]);
        glVertex3f(_box.max[0], _box.min[1], _box.max[2]);
        
        glNormal3f(0.0f, -1.0f, 0.0f);
        glVertex3f(_box.min[0], _box.min[1], _box.min[2]);
        glVertex3f(_box.max[0], _box.min[1], _box.min[2]);
        glVertex3f(_box.max[0], _box.min[1], _box.max[2]);
        glVertex3f(_box.min[0], _box.min[1], _box.max[2]);
        
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(_box.min[0], _box.max[1], _box.min[2]);
        glVertex3f(_box.max[0], _box.max[1], _box.min[2]);
        glVertex3f(_box.max[0], _box.max[1], _box.max[2]);
        glVertex3f(_box.min[0], _box.max[1], _box.max[2]);
    glEnd();
}

template<typename T> inline
void draw_solid(const oxtorne::sphere<T,3>& _sphere) {
    glPushMatrix();
    glTranslatef(_sphere.center[0], _sphere.center[1], _sphere.center[2]);
    glutSolidSphere(_sphere.radius, 16, 16);
    glPopMatrix();
}



};
