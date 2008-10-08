
#define OXMESH_CPP

#include "OxMesh.h"

#include <cstdlib>

namespace oxtorne {

    template<typename T, std::size_t D>
    mesh<T,D>::vvhandle::vvhandle(const vertex* _v) {
        current = base = _v;
    }

    template<typename T, std::size_t D>
    mesh<T,D>::vvhandle::vvhandle(const vvhandle& _other) {
        current = _other.current;
        base    = _other.base;
    }

    template<typename T, std::size_t D>
    typename mesh<T,D>::vertex&
    mesh<T,D>::vvhandle::operator* () const {
        return *_current;
    }

    template<typename T, std::size_t D>
    typename mesh<T,D>::vertex*
    mesh<T,D>::vvhandle::operator->() const {
        return &*_current;
    }
    
    template<typename T, std::size_t D>
    bool
    mesh<T,D>::vvhandle::operator==(const vvhandle& _other) const {
        return _current == _other._current;
    }

    template<typename T, std::size_t D>
    bool
    mesh<T,D>::vvhandle::operator!=(const vvhandle& _other) const {
        return _current != _other.current;
    }

    template<typename T, std::size_t D>
    typename mesh<T,D>::vvhandle&
    mesh<T,D>::vvhandle::operator++() {
        ++_current;
        return *this;
    }

    template<typename T, std::size_t D>
    typename mesh<T,D>::vvhandle
    mesh<T,D>::vvhandle::operator++(const int) {
        vvhandle _previous = *this;
        (*this)++;
        return _previous;
    }

    template<typename T, std::size_t D>
    typename mesh<T,D>::fhandle
    mesh<T,D>::add_face(vhandle _v0, vhandle _v1, vhandle _v2) {

        /*std::cout << (**_v0)[0] << " "  << (**_v0)[1] << " "  << (**_v0)[2] << std::endl;
        std::cout << (**_v1)[0] << " "  << (**_v1)[1] << " "  << (**_v1)[2] << std::endl;
        std::cout << (**_v2)[0] << " "  << (**_v2)[1] << " "  << (**_v2)[2] << std::endl;*/

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
        _he0->vertex = *_v0;
        _he1->vertex = *_v1;
        _he2->vertex = *_v2;

        // halfedges know the following halfedge
        _he0->next = _he1;
        _he1->next = _he2;
        _he2->next = _he0;

        // halfedges know the opposite halfedge (if any)
        hehandle _hehandle = find_edge_from_to(_v2, _v0);
        _he0->opposite = (_hehandle == halfedges.end() ? NULL : *_hehandle);
        _hehandle = find_edge_from_to(_v0, _v1);
        _he1->opposite = (_hehandle == halfedges.end() ? NULL : *_hehandle);
        _hehandle = find_edge_from_to(_v1, _v2);
        _he2->opposite = (_hehandle == halfedges.end() ? NULL : *_hehandle);

        // new structures should be added to the mesh structure
        halfedges.push_back(_he0);
        halfedges.push_back(_he1);
        halfedges.push_back(_he2);
        faces.push_back(_f);

        // we finally return the face that was created
        return --faces.end();
    }

    template<typename T, std::size_t D>
    typename mesh<T,D>::fhandle
    mesh<T,D>::add_face (const point<T,D>& _p0, const point<T,D>& _p1, const point<T,D>& _2) {

        // first off get some vertex handles
        vhandle _vh0 = add_vertex(_p0);
        vhandle _vh1 = add_vertex(_p1);
        vhandle _vh2 = add_vertex(_p2);

        // and create a face
        return add_face(_vh0, _vh1, _vh2);
    }

    template<typename T, std::size_t D>
    typename mesh<T,D>::hehandle
    mesh<T,D>::find_edge_from_to (const vhandle& _from, const vhandle& _to) {

        // iterate over the halfedges
        for (hehandle _iter = halfedges.begin(); _iter != halfedges.end(); ++_iter)
            if ((*_from)->edge == (*_iter) && (*_iter)->vertex == (*_to))

                // the edge we were looking for exists
                return _iter;

        // edge not found, return the end-iterator
        return --halfedges.end();
    }

    template<typename T, std::size_t D>
    typename mesh<T,D>::vhandle
    mesh<T,D>::add_vertex(const point<T,D>& _p) {
        

        // TODO!!
        vertex** v = malloc(sizeof(point<T,D>) * (n_vertices + 1));

        for (int i = 0; i )

        // first create the new vertex (on the heap!)
        vertices.push_back(new vertex());

        // then assign the values
        for (int i = 0; i < D; ++i) vertices.back()->point[i] = _p[i];

        // and at last return the handle
        return vertices.begin() + (vertices.size() - 1);
    }

    template<typename T, std::size_t D>
    typename mesh<T,D>::fhandle
    mesh<T,D>::faces_begin() {
        // start iterator for faces
        return faces.begin();
    }

    template<typename T, std::size_t D>
    typename mesh<T,D>::fhandle
    mesh<T,D>::faces_end() {
        // end iterator for faces
        return faces.end();
    }
    
    template<typename T, std::size_t D>
    typename mesh<T,D>::vhandle
    mesh<T,D>::vertices_begin() {
        // start iterator for vertices
        return vertices.begin();
    }

    template<typename T, std::size_t D>
    typename mesh<T,D>::vhandle
    mesh<T,D>::vertices_end() {
        // end iterator for vertices
        return vertices.end();
    }

    template<typename T, std::size_t D>
    typename mesh<T,D>::hehandle
    mesh<T,D>::edges_begin() {
        // start iterator for edges
        return halfedges.begin();
    }

    template<typename T, std::size_t D>
    typename mesh<T,D>::hehandle
    mesh<T,D>::edges_end() {
        // end iterator for edges
        return halfedges.end();
    }

    template<typename T, std::size_t D>
    typename mesh<T,D>::vvhandle
    mesh<T,D>::vertex_vertex_begin(const vhandle&) {
        return vvhandle(*vhandle);
    }

};
