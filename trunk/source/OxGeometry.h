
#ifndef OXGEOMETRY_H
#define OXGEOMETRY_H

#include <cstddef>
#include <vector>

namespace oxtorne {

/* Geometric Basetype *********************************************************/
class geometric_basetype{};

/* Point Basetype (n dimensional) *********************************************/
template<typename T, size_t D>
class point : public geometric_basetype {

public:
    point() { for (size_t i = 0; i < D; ++i) value[i] = T(0.0); }
   ~point() {}

    point(const point<T,D>& that) {
        for(size_t i = 0; i < D; ++i)
            this->value[i] = that.value[i];
    }
   
    inline point<T,D>& operator=(const point<T,D>& that) {
        for(size_t i = 0; i < D; ++i)
            this->value[i] = that.value[i];
        return *this;
    }

    inline T&       operator[](const size_t& index)       { return value[index]; }
    inline const T& operator[](const size_t& index) const { return value[index]; }

private:
    T value[D];

};

/* Vector Basetype ************************************************************/
template<typename T, size_t D>
class vector : public point<T,D> {

public:
    vector(const vector<T,D>& v) : point<T,D>(v) {}
    vector() :                     point<T,D>()  {}

};

/* Sphere Basetype ************************************************************/
template<typename T, size_t D>
class sphere : public geometric_basetype {

public:
    point<T,D> center;
    T          radius;

};

/* Ray Basetype ***************************************************************/
template<typename T, size_t D>
class ray : public geometric_basetype {

public:
    point<T,D>  origin;
    vector<T,D> direction;

};

/* Plane Basetype *************************************************************/
template<typename T, size_t D>
class plane : public geometric_basetype {

public:
    T           constant;
    vector<T,D> normal;

};

/* Box Basetype ***************************************************************/
template<typename T, size_t D>
class box : public geometric_basetype {

public:
    point<T,D> min, max;

};

/* Line Basetype **************************************************************/
template<typename T, size_t D>
class line : public geometric_basetype {

public:
    point<T,D> a, b;

};

/* Triangle Basetype **********************************************************/
template<typename T, size_t D>
class triangle : public geometric_basetype {

private:
    point<T,D> points[3];

public:
    triangle() {}
   ~triangle() {}

    triangle(const triangle<T,D>& that) {
        this->points[0] = that.points[0];
        this->points[1] = that.points[1];
        this->points[2] = that.points[2];
    }
   
    inline triangle<T,D>& operator=(const triangle<T,D>& that) {
        this->points[0] = that.points[0];
        this->points[1] = that.points[1];
        this->points[2] = that.points[2];
        return *this;
    }

    inline point<T,D>&       operator[](const size_t& index)       { return points[index]; }
    inline const point<T,D>& operator[](const size_t& index) const { return points[index]; }
    inline size_t            size      ()                          { return 3;             }

};

/* Factories ******************************************************************/
template<typename T> inline point<T,2>     make_point(const T&, const T&);
template<typename T> inline point<T,3>     make_point(const T&, const T&, const T&);
template<typename T> inline vector<T,2>    make_vector(const T&, const T&);
template<typename T> inline vector<T,3>    make_vector(const T&, const T&, const T&);
template<typename T> inline sphere<T,3>    make_sphere(const T&, const T&, const T&, const T&);
template<typename T> inline sphere<T,3>    make_sphere(const point<T,3>&, const T&);
template<typename T> inline ray<T,3>       make_ray(const T&, const T&, const T&, const T&, const T&, const T&);
template<typename T> inline ray<T,3>       make_ray(const point<T,3>&, const vector<T,3>&);
template<typename T> inline plane<T,3>     make_plane(const point<T,3>&, const point<T,3>&, const point<T,3>&);
template<typename T> inline plane<T,3>     make_plane(const point<T,3>&, const vector<T,3>&);
template<typename T> inline box<T,2>       make_box(const point<T,2>&, const point<T,2>&);
template<typename T> inline box<T,2>       make_box(const T&, const T&, const T&, const T&);
template<typename T> inline box<T,3>       make_box(const point<T,3>&, const point<T,3>&);
template<typename T> inline box<T,3>       make_box(const T&, const T&, const T&, const T&, const T&, const T&);
template<typename T> inline line<T,3>      make_line(const point<T,3>&, const point<T,3>&);
template<typename T> inline line<T,3>      make_line(const T&, const T&, const T&, const T&, const T&, const T&);
template<typename T> inline triangle<T,3>  make_triangle(const point<T,3>&, const point<T,3>&, const point<T,3>&);
template<typename T> inline triangle<T,3>  make_triangle(const T&, const T&, const T&, const T&, const T&, const T&, const T&, const T&, const T&);

/* Algebraic Operations *******************************************************/
template<typename T, size_t D> inline bool        operator==(const point<T,D>&, const point<T,D>&);
template<typename T, size_t D> inline point<T,D>  operator+ (const point<T,D>&, const point<T,D>&);
template<typename T, size_t D> inline vector<T,D> operator+ (const vector<T,D>&, const vector<T,D>&);
template<typename T, size_t D> inline vector<T,D> operator- (const point<T,D>&, const point<T,D>&);
template<typename T, size_t D> inline point<T,D>  operator* (const point<T,D>&, const T&);
template<typename T, size_t D> inline vector<T,D> operator* (const vector<T,D>&, const T&);
template<typename T, size_t D> inline point<T,D>  operator* (const T&, const point<T,D>&);
template<typename T, size_t D> inline vector<T,D> operator* (const T&, const vector<T,D>&);

/* Containment Checks *********************************************************/
template<typename T, size_t D> inline bool box_in_box(const box<T,D>&, const box<T,D>&);

/* Vector Calculations ********************************************************/
template<typename T> inline T              length(const vector<T,3>&);
template<typename T> inline T              distance(const point<T,3>&, const point<T,3>&);
template<typename T> inline vector<T,3>    normalize(const vector<T,3>&);
template<typename T> inline vector<T,3>    cross_product(const vector<T,3>&, const vector<T,3>&);
template<typename T> inline T              dot_product(const point<T,3>&, const point<T,3>&);

/* Containment Checks *********************************************************/
template<typename T> inline bool           point_in_box(const box<T,2>&, const point<T,2>&);
template<typename T> inline bool           point_in_box(const box<T,3>&, const point<T,3>&);
template<typename T> inline bool           point_in_box(const box<T,3>&, const T&, const T&, const T&);

/* Itersection Checks *********************************************************/
template<typename T> inline bool           intersect(const box<T,3>&, const triangle<T,3>&);
template<typename T> inline bool           intersect(const line<T,3>&, const plane<T,3>&);
template<typename T> inline bool           intersect(const ray<T,3>&, const plane<T,3>&);
template<typename T> inline bool           intersect(const triangle<T,3>&, const line<T,3>&);
template<typename T> inline bool           intersect(const triangle<T,3>&, const ray<T,3>&);
template<typename T> inline bool           intersect(const triangle<T,3>&, const sphere<T,3>&);

/* Intersection Locations *****************************************************/
template<typename T> inline point<T,3>     intersection_point(const line<T,3>&, const plane<T,3>&);
template<typename T> inline point<T,3>     intersection_point(const ray<T,3>&, const plane<T,3>&);
template<typename T> inline point<T,3>     intersection_point(const line<T,3>&, const triangle<T,3>&);
template<typename T> inline void           intersection_point(const sphere<T,3>&, const ray<T,3>&, point<T,3>*&, int&);

/* Cleset Point Calculations **************************************************/
template<typename T> inline point<T,3>     closest_point_on_ray_from_point(const ray<T,3>&, const point<T,3>&);
template<typename T> inline point<T,3>     closest_point_on_line_from_point(const line<T,3>&, const point<T,3>&);
template<typename T> inline point<T,3>     closest_point_on_plane_from_point(const plane<T,3>&, const point<T,3>&);
template<typename T> inline point<T,3>     closest_point_on_triangle_from_point(const triangle<T,3>&, const point<T,3>&);

/* Bounding Sphere Calculations ***********************************************/
template<typename T> inline sphere<T,3>    minimum_bounding_sphere(const triangle<T,3>&);
template<typename T> inline sphere<T,3>    minimum_bounding_sphere(const box<T,3>&);

/* Mirror Positions On Geometric Objects **************************************/
template<typename T> inline point<T,3>     mirror(const plane<T,3>&, const point<T,3>&);
template<typename T> inline vector<T,3>    mirror(const plane<T,3>&, const vector<T,3>&);

};

#include "OxGeometry.cpp"

#endif
