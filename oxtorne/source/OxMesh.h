
#ifndef OXMESH_H
#define OXMESH_H

#include "OxGeometry.h"

#include <vector>

namespace oxtorne {

    template <typename T, std::size_t D> class vertex;
    template <typename T, std::size_t D> class face;
    template <typename T, std::size_t D> class halfedge;

    template<typename T, std::size_t D>
    class vertex {
    public:
        halfedge<T,D>* edge;
        point<T,D> point;
    };

    template<typename T, std::size_t D>
    class face { public: halfedge<T,D>* edge; };

    template<typename T, std::size_t D>
    class halfedge {
    public:
        face<T,D>* face;
        vertex<T,D>* vertex;
        halfedge<T,D>* opposite;
        halfedge<T,D>* next;

    };

    /* Mesh type ********************************************************/
    template<typename T, std::size_t D>
    class mesh {

    public:

        typedef typename face<T,D> face;
        typedef typename vertex<T,D> vertex;
        typedef typename halfedge<T,D> halfedge;
        
        typedef typename face** fhandle;
        typedef typename vertex** vhandle;
        typedef typename halfedge** hehandle;

        class vvhandle {
        public:
            vvhandle(const vertex*);
            vvhandle(const vvhandle&);

            vertex& operator* () const;
            vertex* operator->() const;

            bool operator==(const vvhandle&) const;
            bool operator!=(const vvhandle&) const;
            vvhandle& operator++();
            vvhandle  operator++(const int);

        protected:
            vertex* current;
            vertex* base;
        };

        mesh() { faces(0); vertices(0); halfedges(0);}
       ~mesh() {}

        fhandle  add_face          (vhandle, vhandle, vhandle);
        fhandle  add_face          (const point<T,D>&, const point<T,D>&, const point<T,D>&);
        hehandle find_edge_from_to (const vhandle&,    const vhandle&);
        vhandle  add_vertex        (const point<T,D>&);

        fhandle  faces_begin();
        fhandle  faces_end();
        vhandle  vertices_begin();
        vhandle  vertices_end();
        hehandle edges_begin();
        hehandle edges_end();
        vvhandle vertex_vertex_begin(const vhandle&);

    protected:

        std::size_t n_faces();
        std::size_t n_vertices();
        std::size_t n_halfedges();

        face** faces;
        vertex** vertices;
        halfedge** halfedges;

    };

}; // namespace oxtorne

#if !defined(OXMESH_CPP)
#include "OxMesh.cpp"
#endif

#endif // OXMESH_H
