
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
    _box.min[0] = std::min(_a[0], _b[0]);
    _box.min[1] = std::min(_a[1], _b[1]);
    _box.min[2] = std::min(_a[2], _b[2]);
    _box.max[0] = std::max(_a[0], _b[0]);
    _box.max[1] = std::max(_a[1], _b[1]);
    _box.max[2] = std::max(_a[2], _b[2]);
    return _box;
}

template<typename T>
box<T,3> make_box(const T& _ax, const T& _ay, const T& _az, const T& _bx, const T& _by, const T& _bz) {
    box<T,3> _box;
    _box.min[0] = std::min(_ax, _bx);
    _box.min[1] = std::min(_ay, _by);
    _box.min[2] = std::min(_az, _bz);
    _box.max[0] = std::min(_ax, _bx);
    _box.max[1] = std::min(_ay, _by);
    _box.max[2] = std::min(_az, _bz);
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

template<typename T>
triangle<T,3> make_triangle(const point<T,3>& _p0, const point<T,3>& _p1, const point<T,3>& _p2) {
    triangle<T,3> _triangle;
    _triangle[0] = _p0;
    _triangle[1] = _p1;
    _triangle[2] = _p2;
    return _triangle;
}

template<typename T> triangle<T,3> make_triangle(const T& _x, const T& _y, const T& _z, const T& _u, const T& _v, const T& _w, const T& _a, const T& _b, const T& _c) {
    triangle<T,D> _triangle;
    _triangle[0] = make_point(_x, _y, _z);
    _triangle[1] = make_point(_u, _v, _w);
    _triangle[2] = make_point(_a, _b, _c);
    return triangle;
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
point<T,D>  operator*(const T& _scalar, const point<T,D>& _point) {
    point<T,D> _result;
    // compiler loop unroll desired here
    for (int i = 0; i < D; ++i)
        _result[i] = _point[i] * _scalar;
    return _result;
}

template<typename T, std::size_t D>
vector<T,D> operator*(const T& _scalar, const vector<T,D>& _vector) {
    vector<T,D> _result;
    // compiler loop unroll desired here
    for (int i = 0; i < D; ++i)
        _result[i] = _vector[i] * _scalar;
    return _result;
}

template<typename T>
bool
is_equal(const T& _a, const T& _b) {
    T _d = _a - _b;
    return -T(1E-5) <= _d && _d <= T(1E-5);
}

template<typename T>
bool is_beyond(const triangle<T,3>& _triangle, const ray<T,3>& _ray, const T& _radius) {
    point<T,3> _point = closest_point_on_triangle_from_point(_triangle, _ray.origin);
    if (distance(_point, _ray.origin) > _radius)
        return true;
    return false;
}

template<typename T>
T length(const vector<T,3>& _v) {
    return sqrt(_v[0] * _v[0] + _v[1] * _v[1] + _v[2] * _v[2]);
}

template<typename T>
T distance(const point<T,3>& _p0, const point<T,3>& _p1) {
    return sqrt(
        (_p0[0] - _p1[0]) * (_p0[0] - _p1[0]) +
        (_p0[1] - _p1[1]) * (_p0[1] - _p1[1]) +
        (_p0[2] - _p1[2]) * (_p0[2] - _p1[2]));
}

template<typename T>
vector<T,3> normalize(const vector<T,3>& _v) {
    T _length = sqrt(_v[0] * _v[0] + _v[1] * _v[1] + _v[2] * _v[2]);
    
    vector<T,3> _normalized;
    _normalized[0] = _v[0] / _length;
    _normalized[1] = _v[1] / _length;
    _normalized[2] = _v[2] / _length;
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
    return _a[0] * _b[0] + _a[1] * _b[1] + _a[2] * _b[2];
}
   
template<typename T>
bool point_in_box(const box<T,3>& _box, const point<T,3>& _point) {
    return (_box.min[0] <= _point[0]) && (_box.max[0] >= _point[0]) &&
           (_box.min[1] <= _point[1]) && (_box.max[1] >= _point[1]) &&
           (_box.min[2] <= _point[2]) && (_box.max[2] >= _point[2]);
}

template<typename T>
bool point_in_box(const box<T,3>& _box, const T& _x, const T& _y, const T& _z) {
    return _box.min[0] <= _x && _box.min[1] <= _y &&
           _box.min[2] <= _z && _box.max[0] >= _x &&
           _box.max[1] >= _y && _box.max[2] >= _z;
}

template<typename T>
bool intersect(const box<T,3>& _box, const triangle<T,3>& _triangle) {
    point<T,3> _p0 = _triangle[0];
    point<T,3> _p1 = _triangle[1];
    point<T,3> _p2 = _triangle[2];

    if (point_in_box(_box, _p0)) return true;
    if (point_in_box(_box, _p1)) return true;
    if (point_in_box(_box, _p2)) return true;
    
    // TODO eine etwas umfangreiche ueberprüfung!
    return false;
}

template<typename T, std::size_t D>
bool intersect(const line<T,D>& _line, const plane<T,D>& _plane) {
    return dot_product(_line.a - _line.b, _plane.normal) != T(0.0);
}

template<typename T>
bool intersect(const ray<T,3>& _ray, const plane<T,3>& _plane) {
    return dot_product(_ray.direction, _plane.normal) != T(0.0);
}

template<typename T>
bool intersect(const triangle<T,3>& _triangle, const line<T,3>& _line) {
	T edge1_x = _triangle[1][0] - _triangle[0][0];
	T edge1_y = _triangle[1][1] - _triangle[0][1];
	T edge1_z = _triangle[1][2] - _triangle[0][2];
	T edge2_x = _triangle[2][0] - _triangle[0][0];
	T edge2_y = _triangle[2][1] - _triangle[0][1];
	T edge2_z = _triangle[2][2] - _triangle[0][2];

	T pvec_x = (_line.b[1] - _line.a[1]) * edge2_z - (_line.b[2] - _line.a[2]) * edge2_y;
	T pvec_y = (_line.b[2] - _line.a[2]) * edge2_x - (_line.b[0] - _line.a[0]) * edge2_z;
	T pvec_z = (_line.b[0] - _line.a[0]) * edge2_y - (_line.b[1] - _line.a[1]) * edge2_x;

	T det = edge1_x * pvec_x + edge1_y * pvec_y + edge1_z * pvec_z;

	if (is_equal(det,T(0.0))) return false;

	T inv_det = T(1.0) / det;

	T tvec_x = _line.a[0] - _triangle[0][0];
	T tvec_y = _line.a[1] - _triangle[0][1];
	T tvec_z = _line.a[2] - _triangle[0][2];

	T u = (tvec_x * pvec_x + tvec_y * pvec_y + tvec_z * pvec_z) * inv_det;

	if (u < 0.0 || u > 1.0) return false;

	T qvec_x = tvec_y * edge1_z - tvec_z * edge1_y;
	T qvec_y = tvec_z * edge1_x - tvec_x * edge1_z;
	T qvec_z = tvec_x * edge1_y - tvec_y * edge1_x;

	T v = ((_line.b[0] - _line.a[0]) * qvec_x +
	       (_line.b[1] - _line.a[1]) * qvec_y +
		   (_line.b[2] - _line.a[2]) * qvec_z) * inv_det;

	if ((v < 0.0) || ((u + v) > 1.0)) return false;

	return true;
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
point<T,3> intersection_point(const line<T,3>& _line, const triangle<T,3>& _triangle) {
      T _ux = _triangle[1][0] - _triangle[0][0];
      T _uy = _triangle[1][1] - _triangle[0][1];
      T _uz = _triangle[1][2] - _triangle[0][2];

      T _vx = _triangle[2][0] - _triangle[0][0];
      T _vy = _triangle[2][1] - _triangle[0][1];
      T _vz = _triangle[2][2] - _triangle[0][2];

      T _nx = _uy * _vz - _uz * _vy;
      T _ny = _uz * _vx - _ux * _vz;
      T _nz = _ux * _vy - _uy * _vx;

      T _dirx = _line.b[0] - _line.a[0];
      T _diry = _line.b[1] - _line.a[1];
      T _dirz = _line.b[2] - _line.a[2];

      T _w0x  = _line.a[0] - _triangle[0][0];
      T _w0y  = _line.a[1] - _triangle[0][1];
      T _w0z  = _line.a[2] - _triangle[0][2];

      T _a = (_nx * _w0x  + _ny * _w0y  + _nz * _w0z) * T(-1.0);
      T _b =  _nx * _dirx + _ny * _diry + _nz * _dirz;
      T _r =   _a / _b;

      return make_point(_line.a[0] + (_r * _dirx),
                        _line.a[1] + (_r * _diry),
                        _line.a[2] + (_r * _dirz));
}

template<typename T>
std::vector<point<T,3> > intersection_point(const sphere<T,3>& _sphere, const ray<T,3>& _ray) {
    
    std::vector<point<T,3> > _results;

    vector<T,3> _v = _ray.origin - _sphere.center;
    T _a = dot_product(_v, _v) - (_sphere.radius * _sphere.radius);
    T _b = dot_product(_ray.direction, _v) * T(2.0);
    T _c = dot_product(_ray.direction, _ray.direction);

    T _b2 = _b * _b;
    T _d = _b2 - (T(4.0) * _a * _c);

    if (_d < T(0.0))
        return _results;

    if (is_equal(_d, T(0.0))) {
        _results.push_back(_ray.origin + _ray.direction * (-_b / (T(2.0) * _a)));
        return _results;
    }

    T _disc = _b2 - (T(4.0) * _a * _c);
    T _deno = T(2.0) * _a;

    _results.push_back(_ray.origin + _ray.direction * ((-_b + _disc) / _deno));
    _results.push_back(_ray.origin + _ray.direction * ((-_b - _disc) / _deno));

    return _results;
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

template<typename T>
point<T,3> closest_point_on_triangle_from_point(const triangle<T,3>& _triangle, const point<T,3>& _point) {
    vector<T,3> ab = _triangle[1] - _triangle[0];
    vector<T,3> ac = _triangle[2] - _triangle[0];
    vector<T,3> bc = _triangle[2] - _triangle[1];

    T snominator   = dot_product(_point - _triangle[0], ab);
    T sdenominator = dot_product(_point - _triangle[1], _triangle[0] - _triangle[1]);

    T tnominator   = dot_product(_point - _triangle[0], ac);
    T tdenominator = dot_product(_point - _triangle[2], _triangle[0] - _triangle[2]);

    if (snominator <= T(0.0) && tnominator <= T(0.0))
       return _triangle[0];

    T unominator   = dot_product(_point - _triangle[1], bc);
    T udenominator = dot_product(_point - _triangle[2], _triangle[1] - _triangle[2]);

    if ((sdenominator <= T(0.0)) && (unominator <= T(0.0)))
       return _triangle[1];

    if ((tdenominator <= T(0.0)) && (udenominator <= T(0.0)))
       return _triangle[2];

    vector<T,3> n = cross_product((_triangle[1] - _triangle[0]), (_triangle[2] - _triangle[0]));
    
    T dot_a = dot_product(n, cross_product((_triangle[0] - _point), (_triangle[1] - _point)));

    if ((dot_a <= T(0.0)) && (snominator >= T(0.0)) && (sdenominator >= T(0.0)))
       return _triangle[0] + ab * (snominator / (snominator + sdenominator));

    T dot_b = dot_product(n,cross_product((_triangle[1] - _point), (_triangle[2] - _point)));

    if (dot_b <= T(0.0) && unominator >= T(0.0) && udenominator >= T(0.0))
       return _triangle[1] + (bc * (unominator / (unominator + udenominator)));

    T dot_c = dot_product(n, cross_product((_triangle[2] - _point), (_triangle[0] - _point)));

    if ((dot_c <= T(0.0)) && (tnominator >= T(0.0)) && (tdenominator >= T(0.0)))
        return _triangle[0] + ac * (tnominator / (tnominator + tdenominator));

    T u = dot_b / (dot_b + dot_c + dot_a);
    T v = dot_c / (dot_b + dot_c + dot_a);
    T w = T(1.0) - u - v;
    return (_triangle[0] * u) + (_triangle[1] * v) + (_triangle[2] * w);
}

template<typename T>
sphere<T,3> minimum_bounding_sphere(const triangle<T,3>& _triangle) {

    point<T,3> A = _triangle[0];
	point<T,3> B = _triangle[1];
	point<T,3> C = _triangle[2];

    T dotABAB = dot_product(B - A, B - A);
    T dotABAC = dot_product(B - A, C - A);
    T dotACAC = dot_product(C - A, C - A);

    T d = T(2.0) * (dotABAB * dotACAC - dotABAC * dotABAC);
	T s = (dotABAB * dotACAC - dotACAC * dotABAC) / d;
    T t = (dotACAC * dotABAB - dotABAB * dotABAC) / d;

    point<T,3> tp = A;
	sphere<T,3> _sphere;
	point<T,3> _center;

    if (s <= T(0.0)) {
		point<T,3> G = A + C;
        _sphere.center[0] = T(0.5) * G[0];
		_sphere.center[1] = T(0.5) * G[1];
		_sphere.center[2] = T(0.5) * G[2];
    } else if (t <= T(0.0)) {
        point<T,3> G = A + B;
		_sphere.center[0] = T(0.5) * G[0];
		_sphere.center[1] = T(0.5) * G[1];
		_sphere.center[2] = T(0.5) * G[2];
    } else if (s + t >= T(1.0)) {
        point<T,3> G = C + B;
		_sphere.center[0] = T(0.5) * G[0];
		_sphere.center[1] = T(0.5) * G[1];
		_sphere.center[2] = T(0.5) * G[2];
        tp = B;
    } else {
		point<T,3> G = B - A;
		point<T,3> H = C - A;
		_sphere.center[0] = A[0] + s * G[0] + t * H[0];
		_sphere.center[1] = A[1] + s * G[1] + t * H[1];
		_sphere.center[2] = A[2] + s * G[2] + t * H[2];
	}

	_center.x = _sphere.x;
	_center.y = _sphere.y;
	_center.z = _sphere.z;

	_sphere.radius = sqrt(dot_product(_center - tp, _center - tp));

	return _sphere;
}

template<typename T>
sphere<T,3> minimum_bounding_sphere(const box<T,3>& _box) {
    sphere<T,3> _sphere;
    _sphere.center = (_box.min + _box.max) * T(0.5);
    _sphere.radius = distance(_sphere.center, _box.max);
    return _sphere;
}

}
