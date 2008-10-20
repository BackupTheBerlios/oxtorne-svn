
#define OXVISUALIZE_CPP

#include "OxVisualize.h"

namespace oxtorne{

template<typename T>
GLuint
wire(const box<T, 3>& _box) {
	GLuint _reference = glGenLists(1);
	glNewList(_reference, GL_COMPILE);
	
	glLineWidth(1.0);
	glColor3f(0.0, 0.0, 0.0);
	glDisable(GL_LIGHTING);

	float low_x = _box.min[0];
	float low_y = _box.min[1];
	float low_z = _box.min[2];
	float up_x = _box.max[0];
	float up_y = _box.max[1];
	float up_z = _box.max[2];
	glBegin(GL_LINE_STRIP);
		glVertex3f(low_x, low_y, low_z);
		glVertex3f(up_x, low_y, low_z);
		glVertex3f(up_x, up_y, low_z);
		glVertex3f(low_x, up_y, low_z);
		glVertex3f(low_x, low_y, low_z);
	
		glVertex3f(low_x, low_y, up_z);
		glVertex3f(up_x, low_y, up_z);
		glVertex3f(up_x, up_y, up_z);
		glVertex3f(low_x, up_y, up_z);
		glVertex3f(low_x, low_y, up_z);
	glEnd();
	
	glBegin(GL_LINES);
		glVertex3f(up_x, low_y, low_z);
		glVertex3f(up_x, low_y, up_z);
		glVertex3f(up_x, up_y, low_z);
		glVertex3f(up_x, up_y, up_z);
		glVertex3f(low_x, up_y, low_z);
		glVertex3f(low_x, up_y, up_z);
	glEnd();

	glEndList();
	return _reference;
}

template<typename T>
GLuint
wire(const line<T, 3>& _line) {
	GLuint _reference = glGenLists(1);
	glNewList(_reference, GL_COMPILE);
	
	glLineWidth(1.0);
	glColor3f(1.0, 0.0, 0.0);
	glDisable(GL_LIGHTING);
	
	glBegin(GL_LINES);
		glVertex3f(_line.a[0], _line.a[1], _line.a[2]);
		glVertex3f(_line.b[0], _line.b[1], _line.b[2]);
	glEnd();
	
	glEndList();
	return _reference;
}

template<typename T>
GLuint
wire(const ray<T, 3>& _ray) {
	GLuint _reference = glGenLists(1);
	glNewList(_reference, GL_COMPILE);
	
	glLineWidth(1.0);
	glColor3f(0.0, 1.0, 0.0);
	glDisable(GL_LIGHTING);
	
	glBegin(GL_LINES);
		glVertex3f(_ray.origin[0],                     _ray.origin[1],                     _ray.origin[2]);
		glVertex3f(_ray.origin[0] + _ray.direction[0], _ray.origin[1] + _ray.direction[1], _ray.origin[2] + _ray.direction[2]);
	glEnd();
	
	glEndList();
	return _reference;
}

template<typename T>
GLuint
wire(const sphere<T,3>& _sphere) {
	GLuint _reference = glGenLists(1);
	glNewList(_reference, GL_COMPILE);
	
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_LIGHTING);
    glPushMatrix();
	glTranslatef(_sphere.center[0], _sphere.center[1], _sphere.center[2]);
    glutWireSphere(_sphere.radius, 8, 8);
    glPopMatrix();
	
	glEndList();
	return _reference;
}

template<typename T>
GLuint
solid (mesh<T,3>& _mesh) {
    GLuint _reference = glGenLists(1);
	glNewList(_reference, GL_COMPILE);
    glEnable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_TRIANGLES);
	for (mesh<T,3>::fiter f_iter = _mesh.faces_begin(); f_iter != _mesh.faces_end(); ++f_iter) {
        mesh<T,3>::f_handle _fhandle = *f_iter;
        oxtorne::vector<float,3> _v = _mesh.face_normal(_fhandle);
        glNormal3fv(&_v[0]);

        mesh<T,3>::he_handle _he0 = _fhandle->edge;
        glVertex3f((*_he0->vertex)[0], (*_he0->vertex)[1], (*_he0->vertex)[2]); _he0 = _he0->next;
        glVertex3f((*_he0->vertex)[0], (*_he0->vertex)[1], (*_he0->vertex)[2]); _he0 = _he0->next;
        glVertex3f((*_he0->vertex)[0], (*_he0->vertex)[1], (*_he0->vertex)[2]);
    }
    glEnd();
	
    glDisable(GL_LIGHTING);
	glEndList();
	return _reference;
}

template<typename T>
GLuint
solid (const point<T,3>& _point) {
	GLuint _reference = glGenLists(1);
	glNewList(_reference, GL_COMPILE);
	
	glPointSize(3.0);
	glColor3f(0.0, 0.0, 1.0);
	glDisable(GL_LIGHTING);
	
	glBegin(GL_POINTS);
		glVertex3f(_point[0], _point[1], _point[2]);
	glEnd();
	
	glEndList();
	return _reference;
}

template<typename T>
GLuint
solid(const sphere<T,3>& _sphere) {
	GLuint _reference = glGenLists(1);
	glNewList(_reference, GL_COMPILE);
	
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_LIGHTING);
    glPushMatrix();
	glTranslatef(_sphere.center[0], _sphere.center[1], _sphere.center[2]);
	glutSolidSphere(_sphere.radius, 8, 8);
    glPopMatrix();
	
	glEndList();
	return _reference;
}

template<typename T>
GLuint
solid(const triangle<T, 3>& _triangle) {
    GLuint _reference = glGenLists(1);
	glNewList(_reference, GL_COMPILE);
	
	glLineWidth(1.0);
	glColor3f(1.0, 0.0, 0.0);
	glDisable(GL_LIGHTING);

    glBegin(GL_TRIANGLES);
        glVertex3f(_triangle[0][0], _triangle[0][1], _triangle[0][2]);
        glVertex3f(_triangle[1][0], _triangle[1][1], _triangle[1][2]);
        glVertex3f(_triangle[2][0], _triangle[2][1], _triangle[2][2]);
	glEnd();
    
	glEndList();
	return _reference;
}

template<typename T>
void
coordinate_system (const T& _size) {
    glLineWidth(1.0f);
	glBegin(GL_LINES);
		glColor3f(           1.0,            0.0,            0.0);
		glVertex3f(        T(0.0),         T(0.0),         T(0.0));
		glVertex3f(_size * T(1.0),         T(0.0),         T(0.0));
		glColor3f(           0.0,            1.0,            0.0);
		glVertex3f(        T(0.0),         T(0.0),         T(0.0));
		glVertex3f(        T(0.0), _size * T(1.0),         T(0.0));
		glColor3f(           0.0,            0.0,            1.0);
		glVertex3f(        T(0.0),         T(0.0),         T(0.0));
		glVertex3f(        T(0.0),         T(0.0), _size * T(1.0));
	glEnd();
}

template<typename T>
GLuint
mesh_white(mesh<T,3>& _mesh) {

    GLuint _reference = glGenLists(1);
	glNewList(_reference, GL_COMPILE);
    glDisable(GL_LIGHTING);
	// glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_TRIANGLES);

    for (mesh<T,3>::fiter f_iter = _mesh.faces_begin(); f_iter != _mesh.faces_end(); ++f_iter) {
        mesh<T,3>::f_handle _fhandle = *f_iter;
        mesh<T,3>::he_handle _he0 = _fhandle->edge;
        glVertex3f((*_he0->vertex)[0], (*_he0->vertex)[1], (*_he0->vertex)[2]); _he0 = _he0->next;
        glVertex3f((*_he0->vertex)[0], (*_he0->vertex)[1], (*_he0->vertex)[2]); _he0 = _he0->next;
        glVertex3f((*_he0->vertex)[0], (*_he0->vertex)[1], (*_he0->vertex)[2]);
    }

    glEnd();
	
	glEndList();
	return _reference;
}

};


