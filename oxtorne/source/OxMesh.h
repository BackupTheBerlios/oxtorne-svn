
#ifndef OXMESH_H
#define OXMESH_H

#include <vector>
#include <set>

#include "OxGeometry.h"

namespace oxtorne {

    /* Coparator type *********************************************************/
    template<typename T> struct comparator {
        const bool operator()(const point<T,3>& _p, const point<T,3>& _q) const {
            for (int i = 0; i < 3; ++i)
                if (_p[i] != _q[i]) return _p[i] < _q[i];
            return false;
        }
    };

    /* Forward declarations ***************************************************/
    template <typename T, std::size_t D> class vertex;
    template <typename T, std::size_t D> class face;
    template <typename T, std::size_t D> class halfedge;

    /* Vertex type*************************************************************/
    template<typename T, std::size_t D>
    class vertex : public point<T,D> {
    public:
        vertex() : point<T,D>(), edge(0) {}
        halfedge<T,D>* edge;
    };

    /* Face type **************************************************************/
    template<typename T, std::size_t D>
    class face {
    public:
        face() : edge(0) {}
       ~face() {}
        
        halfedge<T,D>* edge; };

    /* Halfedge Type **********************************************************/
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

    /* Mesh type **************************************************************/
    template<typename T, std::size_t D>
    class mesh {

    public:

        mesh() {}
       ~mesh() {}

        typedef face<T,D> face;
        typedef vertex<T,D> vertex;
        typedef halfedge<T,D> halfedge;

        typedef face* f_handle;
        typedef vertex* v_handle;
        typedef halfedge* he_handle;

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
            fviter(const face*);
            fviter(const fviter&);

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

        fiter           faces_begin()     { return faces.begin();     }
        fiter           faces_end()       { return faces.end();       }
        viter           vertices_begin()  { return vertices.begin();  }
        viter           vertices_end()    { return vertices.end();    }
        heiter          edges_begin()     { return halfedges.begin(); } 
        heiter          edges_end()       { return halfedges.end();   }

        vviter          vertex_vertex_begin(const v_handle&);
        vviter          vertex_vertex_end(const v_handle&);
        fviter          face_vertex_begin(const f_handle&);
        fviter          face_vertex_end(const f_handle&);

        std::size_t     n_faces()         { return faces.size();     }
        std::size_t     n_vertices()      { return vertices.size();  }
        std::size_t     n_halfedges()     { return halfedges.size(); }

    protected:

        std::set<face*> faces;
        std::set<vertex*> vertices;
        std::set<halfedge*> halfedges;

    };

    /* Functionals ************************************************************/
    template<typename T> int create_mesh_from_points(mesh<T,3>&, std::vector<point<T,3> >&);
    template<typename T> int read_binary_stl(mesh<T,3>&, const std::string&);
    template<typename T> int read_ascii_stl(mesh<T,3>&, const std::string&);
    template<typename T> int read_stl(mesh<T,3>&, const std::string&);

    template<typename T> box<T,3> bounding_box(mesh<T,3>&);
    template<typename T> triangle<T,3> make_triangle(mesh<T,3>&, const typename  mesh<T,3>::f_handle&);

}; // namespace oxtorne

#if !defined(OXMESH_CPP)
#include "OxMesh.cpp"
#endif

#endif // OXMESH_H
