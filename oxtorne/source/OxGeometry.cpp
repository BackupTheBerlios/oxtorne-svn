
#define OXGEOMETRY_CPP

#include "OxGeometry.h"

#include <cmath>
#include <algorithm>

namespace oxtorne {

template<typename T>
point<T,3> make_point(const T& _x, const T& _y, const T& _z) {
    point<T,3> _point;
    _point[0] = _x;
    _point[1] = _y;
    _point[2] = _z;
    return _point;
}

template<typename T>
vector<T,3> make_vector(const T& _x, const T& _y, const T& _z) {
    vector<T,3> _vector;
    _vector[0] = _x;
    _vector[1] = _y;
    _vector[2] = _z;
    return _vector;
}

template<typename T>
sphere<T,3> make_sphere(const T& _x, const T& _y, const T& _z, const T& _radius) {
    sphere<T,3> _sphere;
    _sphere.center[0] = _x;
    _sphere.center[1] = _y;
    _sphere.center[2] = _z;
    _sphere.radius = _radius;
    return _sphere;
}

template<typename T>
sphere<T,3> make_sphere(const point<T,3>& _center, const T& _radius) {
    sphere<T,3> _sphere;
    _sphere.center[0] = _center[0];
    _sphere.center[1] = _center[1];
    _sphere.center[2] = _center[2];
    _sphere.radius = _radius;
    return _sphere;
}

template<typename T>
ray<T,3> make_ray(const T& _ox, const T& _oy, const T& _oz, const T& _dx, const T& _dy, const T& _dz) {
    ray<T,3> _ray;
    _ray.origin[0] = _ox;
    _ray.origin[1] = _oy;
    _ray.origin[2] = _oz;
    _ray.direction[0] = _dx;
    _ray.direction[1] = _dy;
    _ray.direction[2] = _dz;
    return _ray;
}

template<typename T>
ray<T,3> make_ray(const point<T,3>& _origin, const vector<T,3>& _direction) {
    ray<T,3> _ray;
    _ray.origin = _origin;
    _ray.direction = _direction;
    return _ray;
}

template<typename T>
plane<T,3> make_plane(const point<T,3>& _a, const point<T,3>& _b, const point<T,3>& _c) {
    plane<T,3> _plane;
    vector<T,3> _v0 = _b - _a;
    vector<T,3> _v1 = _c - _a;
    vector<T,3> _normal = cross(_v0, _v1);
    return make_plane(_a, _normal);
}

template<typename T>
plane<T,3> make_plane(const point<T,3>& _point, const vector<T,3>& _vector) {
    vector<T,3> _normalized = normalize(_vector);
    T _constant = dot_product(_vector, _point);
    plane<T,3> _plane;

    _plane.normal = _normalized;
    _plane.constant = _constant;
    return _plane;
}

template<typename T>
box<T,3> make_box(const point<T,3>& _a, const point<T,3>& _b) {
    box<T,3> _box;
    _box.min.x = std::min(_a.x, _b.x);
    _box.min.y = std::min(_a.y, _b.y);
    _box.min.z = std::min(_a.z, _b.z);
    _box.max.x = std::max(_a.x, _b.x);
    _box.max.y = std::max(_a.y, _b.y);
    _box.max.z = std::max(_a.z, _b.z);
    return _box;
}

template<typename T>
box<T,3> make_box(const T& _ax, const T& _ay, const T& _az, const T& _bx, const T& _by, const T& _bz) {
    box<T,3> _box;
    _box.min.x = std::min(_ax, _bx);
    _box.min.y = std::min(_ay, _by);
    _box.min.z = std::min(_az, _bz);
    _box.max.x = std::min(_ax, _bx);
    _box.max.y = std::min(_ay, _by);
    _box.max.z = std::min(_az, _bz);
    return _box;
}

template<typename T>
line<T,3> make_line(const point<T,3>& _a, const point<T,3>& _b) {
    line<T,3> _line;
    _line.a = _a;
    _line.b = _b;
    return _line;
}

template<typename T>
line<T,3> make_line(const T& _ax, const T& _ay, const T& _az, const T& _bx, const T& _by, const T& _bz) {
    line<T,3> _line;
    _line.a.x = _ax;
    _line.a.y = _ay;
    _line.a.z = _az;
    _line.b.x = _bx;
    _line.b.y = _by;
    _line.b.z = _bz;
    return _line;
}

template<typename T, std::size_t D>
point<T,D> operator+(const point<T,D>& _a, const point<T,D>& _b) {
    point<T,D> _point;
    // compiler loop unroll desired here
    for (int i = 0; i < D; ++i)
        _point[i] = _a[i] + _b[i];
    return _point;
}

template<typename T, std::size_t D>
vector<T,D> operator+(const vector<T,D>& _a, const vector<T,D>& _b) {
    vector<T,D> _vector;
    // compiler loop unroll desired here
    for (int i = 0; i < D; ++i)
        _vector[i] = _a[i] + _b[i];
    return _vector;
}

template<typename T, std::size_t D>
vector<T,D> operator-(const point<T,D>& _a, const point<T,D>& _b) {
    vector<T,D> _vector;
    // compiler loop unroll desired here
    for (int i = 0; i < D; ++i)
        _vector[i] = _a[i] - _b[i];
    return _vector;
}

template<typename T, std::size_t D>
point<T,D> operator*(const point<T,D>& _point, const T& _scalar) {
    point<T,D> _result;
    // compiler loop unroll desired here
    for (int i = 0; i < D; ++i)
        _result[i] = _point[i] * _scalar;
    return _result;
}

template<typename T, std::size_t D>
vector<T,D> operator*(const vector<T,D>& _vector, const T& _scalar) {
    vector<T,D> _result;
    // compiler loop unroll desired here
    for (int i = 0; i < D; ++i)
        _result[i] = _vector[i] * _scalar;
    return _result;
}

template<typename T, std::size_t D>
T length(const vector<T,D>& _vector) {
    T _length = T(0.0);
    // compiler loop unroll desired here
    for (int i = 0; i < D; ++i)
        _length += _vector[i] * _vector[i];
    return sqrt(_length);
}

template<typename T, std::size_t D>
vector<T,D> normalize(const vector<T,D>& _vector) {
    vector<T,D> _normalized;
    T _length = length(_vector);
    // compiler loop unroll desired here
    for (int i = 0; i < D; ++i)
        _normalized[i] = _vector[i] / _length;
    return _normalized;
}

template<typename T>
vector<T,3> cross_product(const vector<T,3>& _a, const vector<T,3>& _b) {
    vector<T,3> _result;
    _result[0] = _a[1] * _b[2] - _a[2] * _b[1];
    _result[1] = _a[2] * _b[0] - _a[0] * _b[2];
    _result[2] = _a[0] * _b[1] - _a[1] * _b[0];
    return _result;
}

template<typename T>
T dot_product(const point<T,3>& _a, const point<T,3>& _b) {
    T _dot_product = T(0.0);
    // compiler loop unroll desired here
    for (int i = 0; i < 3; ++i)
        _dot_product += _a[i] * _b[i];
    return _dot_product;
}
   
template<typename T, std::size_t D>
bool point_in_box(const box<T,D>& _box, const point<T,D>& _point) {
    bool _point_in_box = true;
    // compiler loop unroll desired here
    for (int i = 0; i < D; ++i)
        _point_in_box = _point_in_box && (_box.min[i] <= _point[i]) && (_box.max[i] >= _point[i]);
    return _point_in_box;
}

template<typename T>
bool point_in_box(const box<T,3>& _box, const T& _x, const T& _y, const T& _z) {
    return 
        _box.min[0] <= _x &&
        _box.min[1] <= _y &&
        _box.min[2] <= _z &&
        _box.max[0] >= _x &&
        _box.max[1] >= _y &&
        _box.max[2] >= _z;
}

template<typename T, std::size_t D>
bool intersect(const line<T,D>& _line, const plane<T,D>& _plane) {
    return dot_product(_line.a - _line.b, _plane.normal) != T(0.0);
}

template<typename T, std::size_t D>
bool intersect(const ray<T,D>& _ray, const plane<T,D>& _plane) {
    return dot_product(_ray.direction, _plane.normal) != T(0.0);
}

template<typename T>
point<T,3> intersection_point(const line<T,3>& _line, const plane<T,3>& _plane) {
    ray<T,3> _ray = make_ray(_line.a, _line.b - _line.a);
    return intersection_point(_ray, _plane);
}

template<typename T>
point<T,3> intersection_point(const ray<T,3>& _ray, const plane<T,3>& _plane) {
    T _dot   = dot_product(_ray.origin,    _plane.normal);
    T _unit  = dot_product(_ray.direction, _plane.normal);
    return _ray.direction * ((_dot - _plane.constant) / _unit);
}

template<typename T>
point<T,3> closest_point_on_ray_from_point(const ray<T,3>& _ray, const point<T,3>& _point) {
    T _p = dot_product(_point - _ray.origin, _ray.direction);

    if (_p < 0) return _ray.origin;

    return _ray.origin + (_ray.direction * _p);
}

template<typename T>
point<T,3> closest_point_on_line_from_point(const line<T,3>& _line, const point<T,3>& _point) {
    return _line.a + ((_line.b - _line.a) * dot_product(_point - _line.a, _line.b - _line.a));
}

template<typename T>
point<T,3> closest_point_on_plane_from_point(const plane<T,3>& _plane, const point<T,3>& _point) {
    return _plane.normal * (_plane.constant - dot_product(_plane.normal, _point));
}

}
