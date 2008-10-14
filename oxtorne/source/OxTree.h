
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
    
        node_() { for (int i = 0; i < D; ++i ) nodes[i] = NULL; parent = NULL; }
       ~node_() { for (int i = 0; i < D; ++i ) if (nodes[i]) delete nodes[i];  }

        inline node*       front     ()                               { return nodes[0];     }
        inline const node* front     ()                         const { return nodes[0];     }
        inline node*       back      ()                               { return nodes[D - 1]; }
        inline const node* back      ()                         const { return nodes[D - 1]; }
        inline node*       operator[](const std::size_t& index)       { return nodes[index]; }
        inline const node* operator[](const std::size_t& index) const { return nodes[index]; }
        inline std::size_t size      ()                               { return D;            }

        C value;

    protected:
        node* nodes[D];
        node* parent;

    };

    /* Tree Type ******************************************************************/
    template<typename C, std::size_t D>
    class tree {
    
    public:

        typedef       node_<C,D> node;
        typedef const node_<C,D> const_node;

        tree() { origin = NULL; }
       ~tree() {}

        class iterator_base {
    
        public:
            typedef C   value_type;
            typedef C*  pointer_type;
            typedef C&  reference_type;
        
            iterator_base();
            iterator_base(const_node *);

            C& operator* () const;
            C* operator->() const;
    
            bool operator==(const iterator_base&) const;
            bool operator!=(const iterator_base&) const;

        protected:
            node* value;

        };

        class sibling_iterator : public iterator_base {
            sibling_iterator();
            sibling_iterator(const_node*);
            sibling_iterator(const iterator_base&);
        
            sibling_iterator& operator++();
            sibling_iterator& operator--();
            sibling_iterator  operator++(const int);
            sibling_iterator  operator--(const int);
            sibling_iterator& operator+=(const std::size_t&);
            sibling_iterator& operator-=(const std::size_t&);
        };

        /*class breadth_first_iterator : public iterator_base {
            breadth_first_iterator();
            breadth_first_iterator(const_node*);
            breadth_first_iterator(const iterator_base&);

            breadth_first_iterator& operator++();
            breadth_first_iterator& operator--();
            breadth_first_iterator  operator++(const int);
            breadth_first_iterator  operator--(const int);
            breadth_first_iterator& operator+=(const std::size_t&);
            breadth_first_iterator& operator-=(const std::size_t&);
        };*/

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

        void subdivide_node(const iterator_base&);
        void merge_node    (const iterator_base&);

        inline node&       root()       { return *origin; }
        inline const_node& root() const { return *origin; }

    };

    /* Functionals ******************************************************/
    template<typename T> octree<T,3> make_octree(const mesh<T,3>&);
    template<typename T> octree<T,3> make_octree(const std::vector<triangle<T,3> >&);

};

#if !defined(OXTREE_CPP)
#include "OxTree.cpp"
#endif

#endif















