/*
 *  geometry.h
 *  oxtorne geometry library
 *
 */

#ifndef GEOMETRY_H
#define GEOMETRY_H

typedef struct vector2d {
	double x;
	double y;
} vector2d;
typedef struct vector3d {
	double x;
	double y;
	double z;
} vector3d;
typedef struct sphere   {
	double x;
	double y;
	double z;
	double radius;
} sphere;
typedef struct line3d   {
	vector3d p;
	vector3d q;
} line3d;
typedef struct ray3d    {
	vector3d origin;
	vector3d direction;
} ray3d;
typedef struct plane3d  {
	vector3d normal;
	double scalar;
} plane3d;

vector3d
OX_v3d_plus                 (const vector3d*, const vector3d*),
OX_v3d_minus                (const vector3d*, const vector3d*),
OX_v3d_cross                (const vector3d*, const vector3d*),
OX_v3d_times                (const vector3d*, const double),
OX_v3d_normalize            (const vector3d*);

double
OX_v3d_dot                  (const vector3d*, const vector3d*),
OX_v3d_distance             (const vector3d*, const vector3d*),
OX_l3d_length               (const line3d*);

vector3d
OX_closest_point_on_ray_from_point  (const ray3d*, const vector3d*);

vector2d
OX_make_vector2d            (const double, const double);

vector3d
OX_make_vector3d            (const double, const double, const double);

sphere
OX_make_sphere              (const double, const double, const double, const double);

line3d
OX_make_line3d              (const double, const double, const double, const double, const double, const double);

ray3d
OX_make_ray3d               (const double, const double, const double, const double, const double, const double);

#endif
