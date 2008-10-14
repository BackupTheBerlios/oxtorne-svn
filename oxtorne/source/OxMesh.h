
#ifndef OXMESH_H
#define OXMESH_H

#include <vector>
#include <set>

#include "OxAlgorithm.h"

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

        typedef typename std::set<f_handle>::iterator fiter;
        typedef typename std::set<v_handle>::iterator viter;
        typedef typename std::set<he_handle>::iterator heiter;


        class vviter {
        public:
            vviter(const vertex*);
            vviter(const vviter&);

            vertex& operator* () const;
            vertex* operator->() const;

            bool operator==(const vviter&) const;
            bool operator!=(const vviter&) const;
            vviter& operator++();
            vviter  operator++(const int);

        protected:
            vertex* current;
            vertex* base;
        };


        class fviter {
        public:
            fviter(halfedge*);
            fviter(fviter&);

            vertex& operator* () const;
            vertex* operator->() const;

            bool operator==(const fviter&) const;
            bool operator!=(const fviter&) const;
            fviter& operator++();
            fviter  operator++(const int);

        protected:
            halfedge* current;
            halfedge* base;
        };


        f_handle        add_face          (const v_handle&,   const v_handle&,   const v_handle&);
        f_handle        add_face          (const point<T,D>&, const point<T,D>&, const point<T,D>&);
        he_handle       find_edge_from_to (const v_handle&,   const v_handle&);
        v_handle        add_vertex        (const point<T,D>&);
        vector<T,3>     face_normal       (const f_handle&);


        fiter           faces_begin()     { return faces.begin();    }
        fiter           faces_end()       { return faces.end();      }
        viter           vertices_begin()  { return vertices.begin(); }
        viter           vertices_end()    { return vertices.end();   }
        heiter          edges_begin()     { return edges.begin();    } 
        heiter          edges_end()       { return edges.end();      }

        vviter          vertex_vertex_begin(const v_handle&);
        vviter          vertex_vertex_end(const v_handle&);
        fviter          face_vertex_begin(const f_handle&);
        fviter          face_vertex_end(const f_handle&);

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

    template<typename T> box<T,3> bounding_box(mesh<T,3>&);

}; // namespace oxtorne

#if !defined(OXMESH_CPP)
#include "OxMesh.cpp"
#endif

#endif // OXMESH_H
