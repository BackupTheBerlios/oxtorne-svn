
#include "OxGeometry.h"
#include <OpenGL/gl.h>

namespace oxtorne {

template<typename T> inline
void draw_solid(const oxtorne::box<T, 3>& _box) {

    glBegin(GL_QUAD_STRIP);
        glVertex3f(_box.min[0], _box.min[1], _box.min[2]);
        glVertex3f(_box.max[0], _box.min[1], _box.min[2]);
        glVertex3f(_box.min[0], _box.max[1], _box.min[2]);
        glVertex3f(_box.max[0], _box.max[1], _box.min[2]);
        glVertex3f(_box.min[0], _box.max[1], _box.max[2]);
        glVertex3f(_box.max[0], _box.max[1], _box.max[2]);
        glVertex3f(_box.min[0], _box.min[1], _box.max[2]);
        glVertex3f(_box.max[0], _box.min[1], _box.max[2]);
        glVertex3f(_box.min[0], _box.min[1], _box.min[2]);
        glVertex3f(_box.max[0], _box.min[1], _box.min[2]);
    glEnd();
    
    glBegin(GL_QUADS);
        glVertex3f(_box.min[0], _box.min[1], _box.min[2]);
        glVertex3f(_box.min[0], _box.max[1], _box.min[2]);
        glVertex3f(_box.min[0], _box.max[1], _box.max[2]);
        glVertex3f(_box.min[0], _box.min[1], _box.max[2]);
        
        glVertex3f(_box.max[0], _box.min[1], _box.min[2]);
        glVertex3f(_box.max[0], _box.max[1], _box.min[2]);
        glVertex3f(_box.max[0], _box.max[1], _box.max[2]);
        glVertex3f(_box.max[0], _box.min[1], _box.max[2]);
    glEnd();

}


};
