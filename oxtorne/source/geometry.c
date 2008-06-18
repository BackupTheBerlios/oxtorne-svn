/*
 *  geometry.c
 *  oxtorne geometry library
 *
 */

#include "geometry.h"

#include <math.h>

vector3d OX_v3d_plus (const vector3d* _p1, const vector3d* _p2) {
	vector3d _result;
	_result.x = _p1->x + _p2->x;
	_result.y = _p1->y + _p2->y;
	_result.z = _p1->z + _p2->z;
	return _result;
}

vector3d OX_v3d_minus (const vector3d* _p1, const vector3d* _p2) {
	vector3d _result;
	_result.x = _p1->x - _p2->x;
	_result.y = _p1->y - _p2->y;
	_result.z = _p1->z - _p2->z;
	return _result;
}

vector3d OX_v3d_cross (const vector3d* _p1, const vector3d* _p2) {
	vector3d _result;
	_result.x = (_p1->y * _p2->z) + (_p1->z * _p2->y);
	_result.y = (_p1->z * _p2->x) + (_p1->x * _p2->z);
	_result.z = (_p1->x * _p2->y) + (_p1->y * _p2->x);
	return _result;
}

vector3d OX_v3d_times (const vector3d* _p, const T _d) {
	vector3d _vector;
	_vector.x = _p->x * _d;
	_vector.y = _p->y * _d;
	_vector.z = _p->z * _d;
	return _vector;
}

vector3d OX_v3d_normalize (const vector3d* _p) {
	vector3d _result;
	T _sum = _p->x + _p->y + _p->z;
	_result.x = _p->x / _sum;
	_result.y = _p->y / _sum;
	_result.z = _p->z / _sum;
	return _result;
}

T OX_v3d_dot (const vector3d* _p1, const vector3d* _p2) {
	return (_p1->x * _p2->x) + (_p1->y * _p2->y) + (_p1->z * _p2->z);
}

T OX_v3d_distance (const vector3d* _p1, const vector3d* _p2) {
	return sqrt(pow(_p1->x - _p2->x, 2.0) +
	            pow(_p1->y - _p2->y, 2.0) +
	            pow(_p1->z - _p2->z, 2.0));
}

T OX_l3d_length (const line3d* _line) {
	return OX_v3d_distance(&_line->p, &_line->q);
}

int OX_lp3d_intersect (const line3d* _line, const plane3d* _plane) {
    vector3d _vector = OX_v3d_minus(&_line->p, &_line->q);
    if (OX_v3d_dot(&_vector, &_plane->normal) == 0.0)
        return 0;
    return 1;
}

int OX_rp3d_intersect (const ray3d* _ray, const plane3d* _plane) {
    T _projection = OX_v3d_dot(&_ray->origin, &_plane->normal);
    T _unit = OX_v3d_dot(&_ray->direction, &_plane->normal);
    return ((_projection - _plane->scalar) / _unit > 0.0);
}

vector3d OX_rp3d_intersection_point (const ray3d* _ray, const plane3d* _plane) {
    T _projection = OX_v3d_dot  (&_ray->origin,    &_plane->normal);
    T _unit       = OX_v3d_dot  (&_ray->direction, &_plane->normal);
    vector3d _intersec = OX_v3d_times(&_ray->direction, (_projection - _plane->scalar) / _unit);
    return OX_v3d_plus(&_ray->origin, &_intersec);
}

vector3d OX_closest_point_on_ray_from_point (const ray3d* _ray, const vector3d* _vector) {
    T _x = _vector->x - _ray->origin.x;
	T _y = _vector->y - _ray->origin.y;
	T _z = _vector->z - _ray->origin.z;

    T _projection =
		_x * _ray->direction.x + 
		_y * _ray->direction.y + 
		_z * _ray->direction.z;

    if (_projection < 0) return _ray->origin;

	_x = _ray->direction.x * _projection;
	_y = _ray->direction.y * _projection;
	_z = _ray->direction.z * _projection;
	
    return OX_make_vector3d(
		_ray->origin.x + _x,
		_ray->origin.y + _y,
		_ray->origin.z + _z);
}

vector3d OX_closest_point_on_plane_from_point (const plane3d* _plane, const vector3d* _vector) {
	T _projection =
		_plane->normal.x * _vector->x +
		_plane->normal.y * _vector->y +
		_plane->normal.z * _vector->z;

	T _x = _vector->x - ((_plane->scalar - _projection) * _plane->normal.x);
	T _y = _vector->y - ((_plane->scalar - _projection) * _plane->normal.y); 
	T _z = _vector->z - ((_plane->scalar - _projection) * _plane->normal.z);

	return OX_make_vector3d(_x, _y, _z);
}

vector3d OX_make_vector3d (const T _x, const T _y, const T _z) {
	vector3d _vector;
	_vector.x = _x;
	_vector.y = _y;
	_vector.z = _z;
	return _vector;
}

sphere OX_make_sphere (const T _x, const T _y, const T _z, const T _radius) {
	sphere _sphere;
	_sphere.x = _x;
	_sphere.y = _y;
	_sphere.z = _z;
	_sphere.radius = _radius;
	return _sphere;
}

line3d OX_make_line3d (const T _x1, const T _y1, const T _z1,
                       const T _x2, const T _y2, const T _z2) {
	line3d _line;
	_line.p.x = _x1;
	_line.p.y = _y1;
	_line.p.z = _z1;
	_line.q.x = _x2;
	_line.q.y = _y2;
	_line.q.z = _z2;
	return _line;
}

ray3d OX_make_ray3d (const T _x1, const T _y1, const T _z1,
                     const T _x2, const T _y2, const T _z2) {
	ray3d _ray;
	_ray.origin.x = _x1;
	_ray.origin.y = _y1;
	_ray.origin.z = _z1;
	_ray.direction.x = _x2;
	_ray.direction.y = _y2;
	_ray.direction.z = _z2;
	return _ray;
}


