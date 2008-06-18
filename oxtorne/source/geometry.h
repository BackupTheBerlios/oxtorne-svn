/*
 *  geometry.h
 *  oxtorne geometry library
 *
 */

#ifndef GEOMETRY_H
#define GEOMETRY_H

typedef double T;

typedef struct vector3d		    { T x, y, z;					} vector3d;
typedef struct sphere		    { T x, y, z, radius;			} sphere;
typedef struct line3d		    { vector3d p, q;				} line3d;
typedef struct ray3d		    { vector3d origin, direction;	} ray3d;
typedef struct plane3d		    { vector3d normal; T scalar;	} plane3d;
typedef struct triangle3d	    { vector3d a, b, c;				} triangle3d;

vector3d
    OX3d_cross                  (const vector3d*, const vector3d*),
    OX3d_normalize              (const vector3d*);

T
    OX3d_dot                    (const vector3d*, const vector3d*),
    OX3d_distance               (const vector3d*, const vector3d*);

int
    OX3d_intersect_line_plane   (const line3d*, const plane3d*),
    OX3d_intersect_ray_plane    (const ray3d*, const plane3d*);

vector3d
    OX3d_intersection_point_ray_plane (const ray3d*, const plane3d*),
    OX3d_closest_point_on_ray_from_point (const ray3d*, const vector3d*),
	OX3d_closest_point_on_plane_from_point (const plane3d*, const vector3d*);

vector3d
    OX3d_make_vector            (const T, const T, const T);
sphere
    OX3d_make_sphere            (const T, const T, const T, const T);
line3d
    OX3d_make_line              (const T, const T, const T, const T, const T, const T);
ray3d
    OX3d_make_ray               (const T, const T, const T, const T, const T, const T);

#endif
