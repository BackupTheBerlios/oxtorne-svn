
#ifndef OXGEOMETRY_H
#define OXGEOMETRY_H

#include <cstddef>
#include <vector>

#include "OxMath.h"

namespace oxtorne {

/* Simple enum type ***********************************************************/
enum axis { x, y, z };

/* Geometric Basetype *********************************************************/
class geometric_basetype{};

/* Point Basetype (n dimensional) *********************************************/
template<typename T, std::size_t D>
class point : public geometric_basetype {

public:
    typedef       T& reference;
    typedef const T& const_reference;

    point() { for (std::size_t i = 0; i < D; ++i) value[i] = T(0.0); }
   ~point() {}

    inline point<T,D>& operator=(const point<T,D>& _other) {
        if (this == &_other)
            return *this;
        for(std::size_t i = 0; i < D; i++) { value[i] = _other.value[i]; }
        return *this;
    }

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

/* Triangle Basetype **********************************************************/
template<typename T, std::size_t D>
class triangle : public geometric_basetype {

private:
    point<T,D> points[3];

public:
    typedef       point<T,D>& reference;
    typedef const point<T,D>& const_reference;

    inline reference       operator[](const std::size_t& index)       { return points[index]; }
    inline const_reference operator[](const std::size_t& index) const { return points[index]; }
    inline std::size_t     size      ()                               { return 3;             }

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
template<typename T> triangle<T,3>    make_triangle(const point<T,3>&, const point<T,3>&, const point<T,3>&);
template<typename T> triangle<T,3>    make_triangle(const T&, const T&, const T&, const T&, const T&, const T&, const T&, const T&, const T&);


template<typename T, std::size_t D> point<T,D>  operator+(const point<T,D>&, const point<T,D>&);
template<typename T, std::size_t D> vector<T,D> operator+(const vector<T,D>&, const vector<T,D>&);
template<typename T, std::size_t D> vector<T,D> operator-(const point<T,D>&, const point<T,D>&);
template<typename T, std::size_t D> point<T,D>  operator*(const point<T,D>&, const T&);
template<typename T, std::size_t D> vector<T,D> operator*(const vector<T,D>&, const T&);
template<typename T, std::size_t D> point<T,D>  operator*(const T&, const point<T,D>&);
template<typename T, std::size_t D> vector<T,D> operator*(const T&, const vector<T,D>&);


template<typename T> bool             is_equal(const T&, const T&);


template<typename T> bool             is_beyond(const triangle<T,3>&, const ray<T,3>&, const T&);


template<typename T> T                length(const vector<T,3>&);
template<typename T> T                distance(const point<T,3>&, const point<T,3>&);
template<typename T> vector<T,3>      normalize(const vector<T,3>&);
template<typename T> vector<T,3>      cross_product(const vector<T,3>&, const vector<T,3>&);
template<typename T> T                dot_product(const point<T,3>&, const point<T,3>&);


template<typename T> bool             point_in_box(const box<T,3>&, const point<T,3>&);
template<typename T> bool             point_in_box(const box<T,3>&, const T&, const T&, const T&);


template<typename T> bool             intersect(const box<T,3>&, const triangle<T,3>&);
template<typename T> bool             intersect(const line<T,3>&, const plane<T,3>&);
template<typename T> bool             intersect(const ray<T,3>&, const plane<T,3>&);
template<typename T> bool             intersect(const triangle<T,3>&, const line<T,3>&);


template<typename T> point<T,3>               intersection_point(const line<T,3>&, const plane<T,3>&);
template<typename T> point<T,3>               intersection_point(const ray<T,3>&, const plane<T,3>&);
template<typename T> point<T,3>               intersection_point(const line<T,3>&, const triangle<T,3>&);
template<typename T> std::vector<point<T,3> > intersection_point(const sphere<T,3>&, const ray<T,3>&);


template<typename T> point<T,3>       closest_point_on_ray_from_point(const ray<T,3>&, const point<T,3>&);
template<typename T> point<T,3>       closest_point_on_line_from_point(const line<T,3>&, const point<T,3>&);
template<typename T> point<T,3>       closest_point_on_plane_from_point(const plane<T,3>&, const point<T,3>&);
template<typename T> point<T,3>       closest_point_on_triangle_from_point(const triangle<T,3>&, const point<T,3>&);


template<typename T> sphere<T,3>      minimum_bounding_sphere(const triangle<T,3>&);
template<typename T> sphere<T,3>      minimum_bounding_sphere(const box<T,3>&);

};

#if !defined(OXGEOMETRY_CPP)
#include "OxGeometry.cpp"
#endif

#endif
