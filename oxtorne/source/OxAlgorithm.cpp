
#define OXALGORITHM_CPP

#include "OxAlgorithm.h"

namespace oxtorne {

    template<typename T>
    std::vector<box<T, 3> >
    subdivide_box(const box<T, 3>& _box, const int& _dim) {

	// a vector we put the result into
        std::vector<box<T, 3> > results;

	// now create the boxes
	T x1 = _box.min[0], x2 = _box.max[0];
	T y1 = _box.min[1], y2 = _box.max[1];
	T z1 = _box.min[2], z2 = _box.max[2];
	vector<T,3> firstv1 = make_vector(x1, y1, z1);
	vector<T,3> firstv2 = make_vector(x2, y2, z2);
	vector<T,3> secondv1 = make_vector(x1, y1, z1);
	vector<T,3> secondv2 = make_vector(x2, y2, z2);

	// so some distortion
	firstv1[_dim % 3] = ((T(1.0) * firstv1[_dim % 3]) + (T(1.0) * secondv2[_dim % 3])) / T(2.0);
	secondv2[_dim % 3] = T(1.0) * firstv1[_dim % 3];

	// put that into the vector
	results.push_back(make_box(firstv1, firstv2));
	results.push_back(make_box(secondv1, secondv2));

	// compose the result
	if (_dim == 2)
		return results;
	else {
        std::vector<box<T, 3> > additional;
        typename std::vector<box<T,3> >::iterator l_it, tmp_it;
		for (l_it = results.begin(); l_it != results.end(); l_it++) {
            std::vector<box<T,3> > tmp = subdivide_box(*l_it, _dim + 1);
			for (tmp_it = tmp.begin(); tmp_it != tmp.end(); tmp_it++)
				additional.push_back(*tmp_it);
		}
		return additional;
	    }
    }

    template<typename T>
    std::set<typename mesh<T,3>::f_handle>
    intersecting_triangles (mesh<T,3>& _mesh, octree<T,3>& _tree, const line<T,3>& _line, const T& _radius) {
        // build a queue to remember nodes
        typedef octree<T,3>::node node;
        std::queue<node*> _nodes;

        // start iterating
        _nodes.push(_tree.root());

        // collect the faces here
        std::set<mesh<T,3>::f_handle> _faces;

        while(!_nodes.empty()) {
            // prepare next node
            node* _next = _nodes.front();
            _nodes.pop();

            // approximation by using more simple types
            sphere<T,3> _sphere = minimum_bounding_sphere(_next->value.first);
            point<T,3> _point_on_line = closest_point_on_line_from_point(_line, _sphere.center);

            // irrevelant faces
            if (distance(_point_on_line, _sphere.center) > _sphere.radius + _radius)
                continue;
        
            // relevant faces
            if (_next->leaf()) {
                _faces.insert(_next->value.second.begin(), _next->value.second.end());
                continue;
            }

            // leaf not reached yet
            for (std::size_t i = 0; i < _next->size(); ++i)
                _nodes.push(_next->at(i));
        }

        // done
        return _faces;
    }

    template<typename T>
    std::set<typename mesh<T,3>::f_handle>
    intersecting_triangles (mesh<T,3>& _mesh, octree<T,3>& _tree, const ray<T,3>& _ray, const T& _radius) {
        // build a queue to remember nodes
        typedef octree<T,3>::node node;
        std::queue<node*> _nodes;

        // start iterating
        _nodes.push(_tree.root());

        // collect the faces here
        std::set<mesh<T,3>::f_handle> _faces;

        while(!_nodes.empty()) {
            // prepare next node
            node* _next = _nodes.front();
            _nodes.pop();

            // approximation by using more simple types
            sphere<T,3> _sphere = minimum_bounding_sphere(_next->value.first);
            point<T,3> _point_on_line = closest_point_on_ray_from_point(_ray, _sphere.center);

            // irrevelant faces
            if (distance(_point_on_line, _sphere.center) > _sphere.radius + _radius)
                continue;
        
            // relevant faces
            if (_next->leaf()) {
                std::vector<mesh<T,3>::f_handle>::iterator f_iter = _next->value.second.begin();
                std::vector<mesh<T,3>::f_handle>::iterator f_end  = _next->value.second.end();

                for (; f_iter != f_end; ++f_iter) {
                    triangle<T,3> _triangle = make_triangle(_mesh, *f_iter);
                    if (intersect(_triangle, _ray))
                        _faces.insert(*f_iter);
                }

                continue;
            }

            // leaf not reached yet
            for (std::size_t i = 0; i < _next->size(); ++i)
                _nodes.push(_next->at(i));
        }

        // done
        return _faces;
    }

    template<typename T>
    std::set<typename mesh<T,3>::f_handle>
    intersecting_triangles (mesh<T,3>& _mesh, octree<T,3>& _tree, const sphere<T,3>& _sphere) {
        // build a queue to remember nodes
        typedef octree<T,3>::node node;
        std::queue<node*> _nodes;

        // start iterating
        _nodes.push(_tree.root());

        // collect the faces here
        std::set<mesh<T,3>::f_handle> _faces;

        while(!_nodes.empty()) {
            // prepare next node
            node* _next = _nodes.front();
            _nodes.pop();

            // approximation by using more simple types
            sphere<T,3> _s = minimum_bounding_sphere(_next->value.first);

            // irrevelant faces
            if (distance(_s.center, _sphere.center) > _sphere.radius + _s.radius)
                continue;

            // relevant faces
            if (_next->leaf()) {
                _faces.insert(_next->value.second.begin(), _next->value.second.end());
                continue;
            }

            // leaf not reached yet
            for (std::size_t i = 0; i < _next->size(); ++i)
                _nodes.push(_next->at(i));
        }

        // done
        return _faces;
    }

    template<typename T>
    bool
    point_in_mesh (mesh<T,3>& _mesh, octree<T,3>& _tree, const point<T,3>& _point) {
        ray<T,3> _ray = make_ray(_point[0], _point[1], _point[2], T(0.0), T(0.0), T(1.0));
        return (intersecting_triangles(_mesh, _tree, _ray).size() % 2 != 0);
    }

    template<typename T>
    bool
    intersect (mesh<T,3>& _mesh, octree<T,3>& _tree, const sphere<T,3>& _sphere) {
        // spheres inside the mesh should also be removed
        // function missing since not yet required
        if (!intersecting_triangles(_mesh, _tree, _sphere).empty())
            return true;
        return false;
    }

};


