
#define OXMESH_CPP

#include "OxMesh.h"

#include <fstream>
#include <cassert>
#include <map>

namespace oxtorne {

    // vv_iter constructor
    template<typename T, std::size_t D>
    mesh<T,D>::vv_iter::vv_iter(const vertex* _v) {
        current = base = _v;
    }

    // vv_iter copy-constructor
    template<typename T, std::size_t D>
    mesh<T,D>::vv_iter::vv_iter(const vv_iter& _other) {
        current = _other.current;
        base    = _other.base;
    }

    // vv_iter * operator
    template<typename T, std::size_t D>
    typename mesh<T,D>::vertex&
    mesh<T,D>::vv_iter::operator* () const {
        return *_current;
    }

    // vv_iter -> operator
    template<typename T, std::size_t D>
    typename mesh<T,D>::vertex*
    mesh<T,D>::vv_iter::operator->() const {
        return &*_current;
    }
    
    // vv_iter == operator
    template<typename T, std::size_t D>
    bool
    mesh<T,D>::vv_iter::operator==(const vv_iter& _other) const {
        return _current == _other._current;
    }

    // vv_iter != operator
    template<typename T, std::size_t D>
    bool
    mesh<T,D>::vv_iter::operator!=(const vv_iter& _other) const {
        return _current != _other.current;
    }

    // vv_iter ++ operator (post)
    template<typename T, std::size_t D>
    typename mesh<T,D>::vv_iter&
    mesh<T,D>::vv_iter::operator++() {
        ++_current;
        return *this;
    }

    // vv_iter ++ operator (pre)
    template<typename T, std::size_t D>
    typename mesh<T,D>::vv_iter
    mesh<T,D>::vv_iter::operator++(const int) {
        vvhandle _previous = *this;
        (*this)++;
        return _previous;
    }

    template<typename T, std::size_t D>
    mesh<T,D>::fv_iter::fv_iter(halfedge* _he) {
        current = _he;
        base = _he;
    }

    template<typename T, std::size_t D>
    mesh<T,D>::fv_iter::fv_iter(fv_iter& _iter) {
        current = _iter.current;
        base = _iter.base;
    }

    // fv_iter * operator
    template<typename T, std::size_t D>
    typename mesh<T,D>::vertex&
    mesh<T,D>::fv_iter::operator* () const {
        return *current->vertex;
    }
    
    // fv_iter -> operator
    template<typename T, std::size_t D>
    typename mesh<T,D>::vertex*
    mesh<T,D>::fv_iter::operator-> () const {
        return &current->vector;
    }

    // fv_iter == operator
    template<typename T, std::size_t D>
    bool
    mesh<T,D>::fv_iter::operator==(const fv_iter& _fviter) const {
        current == _fviter->current;
    }
    
    // fv_iter != operator
    template<typename T, std::size_t D>
    bool
    mesh<T,D>::fv_iter::operator!=(const fv_iter&) const {
        current != _fvite->current;
    }

    // fv_iter ++ operator (post)
    template<typename T, std::size_t D>
    typename mesh<T,D>::fv_iter& 
    mesh<T,D>::fv_iter::operator++() {
        current = current->next;
        return *this;
    }

    // fv_iter ++ operator (pre)
    template<typename T, std::size_t D>
    typename mesh<T,D>::fv_iter
    mesh<T,D>::fv_iter::operator++(const int) {
        fv_iter copy = *this;
        ++(*this);
        return copy;
    }

    // mesh add_face function
    template<typename T, std::size_t D>
    typename mesh<T,D>::f_handle
    mesh<T,D>::add_face(const v_handle& _v0, const v_handle& _v1, const v_handle& _v2) {

        // create new structures (on the heap!)
        halfedge* _he0 = new halfedge();
        halfedge* _he1 = new halfedge();
        halfedge* _he2 = new halfedge();
        face* _f       = new face();

        // face knows the halfedge
        _f->edge = _he0;

        // halfedges know faces
        _he0->face = _f;
        _he1->face = _f;
        _he2->face = _f;

        // halfedges know vertices they are pointing towards
        _he0->vertex = _v0;
        _he1->vertex = _v1;
        _he2->vertex = _v2;

        // halfedges know the following halfedge
        _he0->next = _he1;
        _he1->next = _he2;
        _he2->next = _he0;

        // halfedges know the opposite halfedge (if any)
        _he0->opposite = find_edge_from_to(_v0, _v2);
        _he1->opposite = find_edge_from_to(_v1, _v0);
        _he2->opposite = find_edge_from_to(_v2, _v1);

        // the opposite edge will know this edge
        if (_he0->opposite != NULL) _he0->opposite->opposite = _he0;
        if (_he1->opposite != NULL) _he1->opposite->opposite = _he1;
        if (_he2->opposite != NULL) _he2->opposite->opposite = _he2;

        // and now the vertices should also know edges
        if (_v0->edge == NULL) _he1;
        if (_v1->edge == NULL) _he2;
        if (_v2->edge == NULL) _he0;

        // new structures should be added to the mesh structure
        halfedges.insert(_he0);
        halfedges.insert(_he1);
        halfedges.insert(_he2);
        faces.insert(_f);

        // we finally return the face that was created
        return _f;
    }

    // mesh add_face function
    template<typename T, std::size_t D>
    typename mesh<T,D>::f_handle
    mesh<T,D>::add_face (const point<T,D>& _p0, const point<T,D>& _p1, const point<T,D>& _2) {
        
        // create new vertices on the heap
        v_handle _vh0 = add_vertex(_p0);
        v_handle _vh1 = add_vertex(_p1);
        v_handle _vh2 = add_vertex(_p2);

        // checks
        assert(_vh0 != NULL);
        assert(_vh1 != NULL);
        assert(_vh2 != NULL);

        // construct a face from the vertices
        return add_face(_v0, _v1, _v2);
    }

    // mesh find_edge_from_to function
    template<typename T, std::size_t D>
    typename mesh<T,D>::he_handle
    mesh<T,D>::find_edge_from_to (const v_handle& _from, const v_handle& _to) {
        // get the outgoing halfedge
        he_handle _he = _from->edge;
        he_handle _first = _he;

        // anything there yet?
        if (_he == NULL || _he->vertex == _to)
            return _he;

        // move to the next outgoing halfedge
        _he = _he->next->next->opposite;

        // retry n times
        while (_he != _first) {
            if (_he == NULL || _he->vertex == _to)
                return _he;
            
            _he = _he->next->next->opposite;
        }

        // found nothing
        return NULL;
    }

    // mesh add_vertex function
    template<typename T, std::size_t D>
    typename mesh<T,D>::v_handle
    mesh<T,D>::add_vertex(const point<T,D>& _p) {
        v_handle _vh = new vertex();
        for (int i = 0; i < D; ++i)
            (*_vh)[i] = _p[i];
        vertices.insert(_vh);
        return _vh;
    }

    // mesh face_normal function
    template<typename T, std::size_t D>
    typename vector<T,3>
    mesh<T,D>::face_normal (const f_handle& _face) {
        
        // get the handles
        he_handle _he0 = _face->edge;
        he_handle _he1 = _he0->next;
        he_handle _he2 = _he1->next;
        
        // sides of the face
        typename vector<T,D> _v = *_he0->vertex - *_he1->vertex;
        typename vector<T,D> _w = *_he0->vertex - *_he2->vertex;

        // checks (cross product defined in 3D)
        assert(D == 3);

        // return the cross product
        return cross_product(_v, _w);
    }

    template<typename T, std::size_t D>
    typename mesh<T,D>::f_iter
    mesh<T,D>::faces_begin() {
        // start iterator for faces
        return faces.begin();
    }

    template<typename T, std::size_t D>
    typename mesh<T,D>::f_iter
    mesh<T,D>::faces_end() {
        // end iterator for faces
        return faces.end();
    }
    
    template<typename T, std::size_t D>
    typename mesh<T,D>::v_iter
    mesh<T,D>::vertices_begin() {
        // start iterator for vertices
        return vertices.begin();
    }

    template<typename T, std::size_t D>
    typename mesh<T,D>::v_iter
    mesh<T,D>::vertices_end() {
        // end iterator for vertices
        return vertices.end();
    }

    template<typename T, std::size_t D>
    typename mesh<T,D>::he_iter
    mesh<T,D>::edges_begin() {
        // start iterator for edges
        return halfedges.begin();
    }

    template<typename T, std::size_t D>
    typename mesh<T,D>::he_iter
    mesh<T,D>::edges_end() {
        // end iterator for edges
        return halfedges.end();
    }

    template<typename T, std::size_t D>
    typename mesh<T,D>::vv_iter
    mesh<T,D>::vertex_vertex_begin(const v_handle& _vh) {
        return vv_iter(_vh);
    }

    template<typename T, std::size_t D>
    typename mesh<T,D>::vv_iter
    mesh<T,D>::vertex_vertex_end(const v_handle& _vh) {
        return vv_iter(_vh);
    }

    template<typename T, std::size_t D>
    typename mesh<T,D>::fv_iter
    mesh<T,D>::face_vertex_begin(const f_handle& _fh) {
        return fv_iter(_fh->edge);
    }

    template<typename T, std::size_t D>
    typename mesh<T,D>::fv_iter
    mesh<T,D>::face_vertex_end(const f_handle& _fh) {
        return fv_iter(_fh->edge);
    }

    template<typename T>
    int
    create_mesh_from_points(mesh<T,3>& _mesh, std::vector<point<T,3> >& _points) {

        // do the normal vector check
        bool _incorrect_normals = false;

        // create something to associate points with pointers
        struct comparator {
            const bool operator()(const point<T,3>& _p, const point<T,3>& _q) const {
                for (int i = 0; i < 3; ++i)
                    if (_p[i] != _q[i]) return _p[i] < _q[i];
                return false;
            }
        };
        
        // the map to map points to pointers
        std::map<point<T,3>, mesh<T,3>::v_handle, comparator> _map;

        // and finally map the points to the pointers
        for (std::size_t i = 0; i < _points.size(); ++i) {
            if (i % 4 == 0) continue; // skip normal vectors
            if (_map.find(_points[i]) == _map.end())
                _map.insert(std::make_pair(_points[i], _mesh.add_vertex(_points[i])));
        }

        // add all points to the mesh
        while (!_points.empty()) {

            mesh<T,3>::v_handle _vh0 = _map[_points.back()]; _points.pop_back();
            mesh<T,3>::v_handle _vh1 = _map[_points.back()]; _points.pop_back();
            mesh<T,3>::v_handle _vh2 = _map[_points.back()]; _points.pop_back();

            // add the face
            mesh<T,3>::f_handle _f0  = _mesh.add_face(_vh2, _vh1, _vh0);

#ifndef NDEBUG
            // test correctness of the normals
            point<T,3>  _p           = _points.back();
            vector<T,3> _normal      = _mesh.face_normal(_f0);
            vector<T,3> _prenorm     = make_vector(_p[0], _p[1], _p[2]);

            // test with the dot product
            if (dot_product(_normal, _prenorm) < T(0.0))
                _incorrect_normals   = true;
#endif

            // pop out the normal
            _points.pop_back();
        }

#ifndef NDEBUG
        if (_incorrect_normals)
            std::cout << "DEBUG: normal vectors don't match orientation" << std::endl;
#endif

        return (_incorrect_normals ? 1 : 0);
    }

    template<typename T>
    int
    read_binary_stl(mesh<T,3>& _mesh, const std::string& _filename) {
        
        // open the file
        std::ifstream _input(_filename.c_str(), std::ios::binary | std::ios::in);

        // number of triangles
        int triangles = 0;

        // read the header
        _input.seekg(80);
        _input.read((char*)&triangles, 4);
        
        //prepare some vectors
        std::vector<point<T,3> > _points;

        // read the file
        while(_input.peek() != EOF) {
            for (int i = 0; i < 4; ++i) {
                float _numbers[3];
                point<T,3> _point;
                _input.read((char*)_numbers, 12);
                
                for (int j = 0; j < 3; ++j)
                    _point[j] = T(_numbers[j]);
                _points.push_back(_point);
            }

            char _trash[2];
            _input.read(_trash, 2);
        }

        // done
        _input.close();

        // done. construct the mesh from that
        return create_mesh_from_points(_mesh, _points);
    }

    template<typename T>
    int
    read_ascii_stl(mesh<T,3>& _mesh, const std::string& _filename) {
        return 1;
    }

    template<typename T>
    int
    read_stl(mesh<T,3>& _mesh, const std::string& _filename) {

        // open the file
        std::ifstream _input(_filename.c_str(), std::ios::binary | std::ios::in);

        // number of triangles
        int triangles = 0;

        // read the header
        _input.seekg(80);
        _input.read((char*)&triangles, 4);
        
        // check if the file size matches (so it is binary)
        char buffer[50];

        // read the file
        while(_input.peek() != EOF) {
            _input.read(buffer, 50);
            triangles = triangles - 1;
        }

        // done
        _input.close();

        // if the filesize matches we know its binary
        if (!triangles)
            return read_binary_stl(_mesh, _filename);
        else
            return read_ascii_stl(_mesh, _filename);
    }


};
