
#ifndef OXGEOMETRY_H
#define OXGEOMETRY_H

#include <cstddef>

#include "OxMath.h"

namespace oxtorne {

/* Geometric Basetype *********************************************************/
class geometric_basetype{};

/* Point Basetype (n dimensional) *********************************************/
template<typename T, std::size_t D>
class point : public geometric_basetype {

public:
    typedef       T& reference;
    typedef const T& const_reference;

    point() {}
   ~point() {}

    inline reference       operator[](const std::size_t& index)       { return value[index]; }
    inline const_reference operator[](const std::size_t& index) const { return value[index]; }

private:
    T value[D];

};

/* Vector Basetype ************************************************************/
template<typename T, std::size_t D>
class vector : public point<T,D> {};

/* Sphere Basetype ************************************************************/
template<typename T, std::size_t D>
class sphere : public geometric_basetype {

public:
    point<T,D>  center;
    T           radius;

};

/* Ray Basetype ***************************************************************/
template<typename T, std::size_t D>
class ray : public geometric_basetype {

public:
    point<T,D>  origin;
    vector<T,D> direction;

};

/* Plane Basetype *************************************************************/
template<typename T, std::size_t D>
class plane : public geometric_basetype {

public:
    T           constant;
    vector<T,D> normal;

};

/* Box Basetype ***************************************************************/
template<typename T, std::size_t D>
class box : public geometric_basetype {

public:
    point<T,D> min, max;

};

/* Line Basetype **************************************************************/
template<typename T, std::size_t D>
class line : public geometric_basetype {

public:
    point<T,D> a, b;

};

/* Operations *****************************************************************/
template<typename T> point<T,3>       make_point(const T&, const T&, const T&);
template<typename T> vector<T,3>      make_vector(const T&, const T&, const T&);
template<typename T> sphere<T,3>      make_sphere(const T&, const T&, const T&, const T&);
template<typename T> sphere<T,3>      make_sphere(const point<T,3>&, const T&);
template<typename T> ray<T,3>         make_ray(const T&, const T&, const T&, const T&, const T&, const T&);
template<typename T> ray<T,3>         make_ray(const point<T,3>&, const vector<T,3>&);
template<typename T> plane<T,3>       make_plane(const point<T,3>&, const point<T,3>&, const point<T,3>&);
template<typename T> plane<T,3>       make_plane(const point<T,3>&, const vector<T,3>&);
template<typename T> box<T,3>         make_box(const point<T,3>&, const point<T,3>&);
template<typename T> box<T,3>         make_box(const T&, const T&, const T&, const T&, const T&, const T&);
template<typename T> line<T,3>        make_line(const point<T,3>&, const point<T,3>&);
template<typename T> line<T,3>        make_line(const T&, const T&, const T&, const T&, const T&, const T&);


template<typename T> point<T,3>       operator+(const point<T,3>&, const point<T,3>&);
template<typename T> vector<T,3>      operator+(const vector<T,3>&, const vector<T,3>&);
template<typename T> vector<T,3>      operator-(const point<T,3>&, const point<T,3>&);
template<typename T> point<T,3>       operator*(const point<T,3>&, const T&);
template<typename T> vector<T,3>      operator*(const vector<T,3>&, const T&);


template<typename T> T                length(const vector<T,3>&);
template<typename T> vector<T,3>      normalize(const vector<T,3>&);
template<typename T> vector<T,3>      cross_product(const vector<T,3>&, const vector<T,3>&);
template<typename T> T                dot_product(const point<T,3>&, const point<T,3>&);


template<typename T> bool             point_in_box(const box<T,3>&, const point<T,3>&);
template<typename T> bool             point_in_box(const box<T,3>&, const T&, const T&, const T&);


template<typename T> bool             intersect(const line<T,3>&, const plane<T,3>&);
template<typename T> bool             intersect(const ray<T,3>&, const plane<T,3>&);


template<typename T> point<T,3>       intersection_point(const line<T,3>&, const plane<T,3>&);
template<typename T> point<T,3>       intersection_point(const ray<T,3>&, const plane<T,3>&);


template<typename T> point<T,3>       closest_point_on_ray_from_point(const ray<T,3>&, const point<T,3>&);
template<typename T> point<T,3>       closest_point_on_line_from_point(const line<T,3>&, const point<T,3>&);
template<typename T> point<T,3>       closest_point_on_plane_from_point(const plane<T,3>&, const point<T,3>&);

};

#if !defined(OXGEOMETRY_CPP)
#include "OxGeometry.cpp"
#endif

#endif
