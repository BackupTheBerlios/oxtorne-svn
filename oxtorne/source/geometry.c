/*
 *  geometry.c
 *  oxtorne geometry library
 *
 */

#include "geometry.h"

#include <math.h>

vector3d OX_v3d_plus (const vector3d* _p1, const vector3d* _p2) {
	struct vector3d _result;
	_result.x = _p1->x + _p2->x;
	_result.y = _p1->y + _p2->y;
	_result.z = _p1->z + _p2->z;
	return _result;
}

vector3d OX_v3d_minus (const vector3d* _p1, const vector3d* _p2) {
	struct vector3d _result;
	_result.x = _p1->x - _p2->x;
	_result.y = _p1->y - _p2->y;
	_result.z = _p1->z - _p2->z;
	return _result;
}

vector3d OX_v3d_cross (const vector3d* _p1, const vector3d* _p2) {
	struct vector3d _result;
	_result.x = (_p1->y * _p2->z) + (_p1->z * _p2->y);
	_result.y = (_p1->z * _p2->x) + (_p1->x * _p2->z);
	_result.z = (_p1->x * _p2->y) + (_p1->y * _p2->x);
	return _result;
}

vector3d OX_v3d_times (const vector3d* _p, const double _d) {
	vector3d _vector;
	_vector.x = _p->x * _d;
	_vector.y = _p->y * _d;
	_vector.z = _p->z * _d;
	return _vector;
}

vector3d OX_v3d_normalize (const vector3d* _p) {
	struct vector3d _result;
	double _sum = _p->x + _p->y + _p->z;
	_result.x = _p->x / _sum;
	_result.y = _p->y / _sum;
	_result.z = _p->z / _sum;
	return _result;
}

double OX_v3d_dot (const vector3d* _p1, const vector3d* _p2) {
	return (_p1->x * _p2->x) + (_p1->y * _p2->y) + (_p1->z * _p2->z);
}

double OX_v3d_distance (const vector3d* _p1, const vector3d* _p2) {
	return sqrt(pow(_p1->x - _p2->x, 2.0) +
	            pow(_p1->y - _p2->y, 2.0) +
	            pow(_p1->z - _p2->z, 2.0));
}

double OX_l3d_length (const line3d* _line) {
	return OX_v3d_distance(&_line->p, &_line->p);
}

vector2d OX_make_vector2d (const double _x, const double _y) {
	vector2d _vector;
	_vector.x = _x;
	_vector.y = _y;
	return _vector;
}

vector3d OX_make_vector3d (const double _x, const double _y, const double _z) {
	vector3d _vector;
	_vector.x = _x;
	_vector.y = _y;
	_vector.z = _z;
	return _vector;
}

sphere OX_make_sphere (const double _x, const double _y, const double _z, const double _radius) {
	sphere _sphere;
	_sphere.x = _x;
	_sphere.y = _y;
	_sphere.z = _z;
	_sphere.radius = _radius;
	return _sphere;
}

line3d OX_make_line3d (const double _x1, const double _y1, const double _z1, const double _x2, const double _y2, const double _z2) {
	line3d _line;
	_line.p.x = _x1;
	_line.p.y = _y1;
	_line.p.z = _z1;
	_line.q.x = _x2;
	_line.q.y = _y2;
	_line.q.z = _z2;
	return _line;
}

ray3d OX_make_ray3d (const double _x1, const double _y1, const double _z1, const double _x2, const double _y2, const double _z2) {
	ray3d _ray;
	_ray.origin.x = _x1;
	_ray.origin.y = _y1;
	_ray.origin.z = _z1;
	_ray.direction.x = _x2;
	_ray.direction.y = _y2;
	_ray.direction.z = _z2;
	return _ray;
}


