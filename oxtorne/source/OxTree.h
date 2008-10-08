
#ifndef OXTREE_H
#define OXTREE_H

#include <vector>

/* Node Type ******************************************************************/
template<typename T, std::size_t D>
class node_ {

public:
    
    typedef       node_<T,D> node;
    typedef const node_<T,D> const_node;
    
    node_() { for (int i = 0; i < D; ++i )     nodes[i] = NULL;           }
   ~node_() { for (int i = 0; i < D; ++i ) if (nodes[i]) delete nodes[i]; }

    inline node*       front     ()                               { return nodes[0];     }
    inline const node* front     ()                         const { return nodes[0];     }
    inline node*       back      ()                               { return nodes[D - 1]; }
    inline const node* back      ()                         const { return nodes[D - 1]; }
    inline node*       operator[](const std::size_t& index)       { return nodes[index]; }
    inline const node* operator[](const std::size_t& index) const { return nodes[index]; }
    inline std::size_t size      ()                               { return D;            }

    T value;

private:
    node* nodes[D];
    node* parent;

};

/* Tree Type ******************************************************************/
template<typename T, std::size_t D>
class tree {
    
public:

    typedef       node_<T,D> node;
    typedef const node_<T,D> const_node;

    tree() {}
   ~tree() {}

    class iterator_base {
    
    public:
        typedef T   value_type;
        typedef T*  pointer_type;
        typedef T&  reference_type;
        
        iterator_base();
        iterator_base(const_node *);

        T& operator* () const;
        T* operator->() const;
    
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

    class breadth_first_iterator : public iterator_base {
        breadth_first_iterator();
        breadth_first_iterator(const_node*);
        breadth_first_iterator(const iterator_base&);

        breadth_first_iterator& operator++();
        breadth_first_iterator& operator--();
        breadth_first_iterator  operator++(const int);
        breadth_first_iterator  operator--(const int);
        breadth_first_iterator& operator+=(const std::size_t&);
        breadth_first_iterator& operator-=(const std::size_t&);
    };

    /*inline node&       root ();
    inline const_node& root () const;
    inline node&       child(const node&, const std::size_t&);
    inline const_node& child(const node&, const std::size_t&) const;
    
    inline node&       next_sibling(const node&);
    inline const_node& next_sibling(const node&) const;
    inline node&       prev_sibling(const node&);
    inline const_node& prev_sibling(const node&) const;
    
    inline bool        has_next_sibling(const node&);
    inline bool        has_prev_sibling(const node&);
    
    inline bool        leaf (const node&);*/

private:
    node* origin;
    
};

#if !defined(OXTREE_CPP)
#include "OxTree.cpp"
#endif

#endif















