
#ifndef OXMESH_H
#define OXMESH_H

#include <vector>
#include <set>

#include "OxGeometry.h"

namespace oxtorne {

    /* Forward declarations *********************************************/
    template <typename T, std::size_t D> class vertex;
    template <typename T, std::size_t D> class face;
    template <typename T, std::size_t D> class halfedge;

    /* Vertex type*******************************************************/
    template<typename T, std::size_t D>
    class vertex : public point<T,D> {
    public:
        vertex() : point(), edge(0) {}
        halfedge<T,D>* edge;
    };

    /* Face type ********************************************************/
    template<typename T, std::size_t D>
    class face {
    public:
        face() : edge(0) {}
       ~face() {}
        
        halfedge<T,D>* edge; };

    /* Halfedge Type ****************************************************/
    template<typename T, std::size_t D>
    class halfedge {
    public:
        halfedge () : face(0), vertex(0), opposite(0), next(0) {}
       ~halfedge () {}

        face<T,D>* face;
        vertex<T,D>* vertex;
        halfedge<T,D>* opposite;
        halfedge<T,D>* next;

    };

    /* Mesh type ********************************************************/
    template<typename T, std::size_t D>
    class mesh {

    public:

        mesh() {}
       ~mesh() {}

        typedef typename face<T,D> face;
        typedef typename vertex<T,D> vertex;
        typedef typename halfedge<T,D> halfedge;

        typedef typename face* f_handle;
        typedef typename vertex* v_handle;
        typedef typename halfedge* he_handle;

        typedef typename std::set<f_handle>::iterator f_iter;
        typedef typename std::set<v_handle>::iterator v_iter;
        typedef typename std::set<he_handle>::iterator he_iter;


        class vv_iter {
        public:
            vv_iter(const vertex*);
            vv_iter(const vv_iter&);

            vertex& operator* () const;
            vertex* operator->() const;

            bool operator==(const vv_iter&) const;
            bool operator!=(const vv_iter&) const;
            vv_iter& operator++();
            vv_iter  operator++(const int);

        protected:
            vertex* current;
            vertex* base;
        };


        class fv_iter {
        public:
            fv_iter(halfedge*);
            fv_iter(fv_iter&);

            vertex& operator* () const;
            vertex* operator->() const;

            bool operator==(const fv_iter&) const;
            bool operator!=(const fv_iter&) const;
            fv_iter& operator++();
            fv_iter  operator++(const int);

        protected:
            halfedge* current;
            halfedge* base;
        };


        f_handle        add_face          (const v_handle&,   const v_handle&,   const v_handle&);
        f_handle        add_face          (const point<T,D>&, const point<T,D>&, const point<T,D>&);
        he_handle       find_edge_from_to (const v_handle&,   const v_handle&);
        v_handle        add_vertex        (const point<T,D>&);
        vector<T,3>     face_normal       (const f_handle&);


        f_iter    faces_begin();
        f_iter    faces_end();
        v_iter    vertices_begin();
        v_iter    vertices_end();
        he_iter   edges_begin();
        he_iter   edges_end();
        vv_iter   vertex_vertex_begin(const v_handle&);
        vv_iter   vertex_vertex_end(const v_handle&);
        fv_iter   face_vertex_begin(const f_handle&);
        fv_iter   face_vertex_end(const f_handle&);

    protected:

        std::set<face*> faces;
        std::set<vertex*> vertices;
        std::set<halfedge*> halfedges;

    };

    /* Functionals ******************************************************/
    template<typename T> int create_mesh_from_points(mesh<T,3>&, std::vector<point<T,3> >&);
    template<typename T> int read_binary_stl(mesh<T,3>&, const std::string&);
    template<typename T> int read_ascii_stl(mesh<T,3>&, const std::string&);
    template<typename T> int read_stl(mesh<T,3>&, const std::string&);

}; // namespace oxtorne

#if !defined(OXMESH_CPP)
#include "OxMesh.cpp"
#endif

#endif // OXMESH_H
