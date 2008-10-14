
#ifndef OXTREE_H
#define OXTREE_H

#include <vector>

#include "OxMesh.h"

namespace oxtorne {

    /* Node Type ******************************************************************/
    template<typename C, std::size_t D>
    class node_ {

    public:
    
        typedef       node_<C,D> node;
        typedef const node_<C,D> const_node;
    
        node_() : parent(0) { for (int i = 0; i < D; ++i ) nodes[i] = NULL; }
       ~node_() { for (int i = 0; i < D; ++i ) if (nodes[i]) delete nodes[i]; }

        inline node*&       front     ()                               { return nodes[0];     }
        inline const node*& front     ()                         const { return nodes[0];     }
        inline node*&       back      ()                               { return nodes[D - 1]; }
        inline const node*& back      ()                         const { return nodes[D - 1]; }
        inline node*&       operator[](const std::size_t& index)       { return nodes[index]; }
        inline const node*& operator[](const std::size_t& index) const { return nodes[index]; }
        inline node*&       at        (const std::size_t& index)       { return nodes[index]; }
        inline const node*& at        (const std::size_t& index) const { return nodes[index]; }
        inline std::size_t  size      ()                               { return D;            }
               bool         leaf      ();
               std::size_t  depth     ();

        C value;

        node* parent;

    protected:
        node* nodes[D];

    };

    /* Tree Type ******************************************************************/
    template<typename C, std::size_t D>
    class tree {
    
    public:

        typedef       node_<C,D> node;
        typedef const node_<C,D> const_node;

        tree() { origin = NULL; }
       ~tree() {}

    protected:
        node* origin;
    
    };

    /* Octree Type ****************************************************************/
    template<typename T, std::size_t D>
    class octree : public tree<std::pair<box<T,D>,std::vector<typename mesh<T,D>::f_handle> >, 8> {
        
    public:

        typedef       box<T,D> cuboid;
        typedef const box<T,D> const_cuboid;
        typedef       std::vector<typename mesh<T,D>::f_handle> faces;
        typedef const std::vector<typename mesh<T,D>::f_handle> const_faces;
        typedef       node_<std::pair<cuboid, faces>,8> node;
        typedef const node_<std::pair<const_cuboid, const_faces>,8> const_node;

        octree(const box<T,D>&);
       ~octree();

        inline       node* root()       { return origin; }
        inline const node* root() const { return origin; }
       
        void subdivide_node (node*);
        void add_face       (mesh<T,3>&, const typename mesh<T,3>::f_handle&);

    };

    /* Functionals ******************************************************/
    template<typename T> octree<T,3> make_octree(mesh<T,3>&, const std::size_t&);

};

#if !defined(OXTREE_CPP)
#include "OxTree.cpp"
#endif

#endif















