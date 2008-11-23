
#ifndef OXTREE_H
#define OXTREE_H

#include <iterator>
#include "OxMesh.h"


namespace oxtorne {

    /* Node Type ******************************************************************/
    template<typename C>
    class node {

    public:
        node() : parent(0), first_child(0), last_child(0), next_sibling(0), last_sibling(0) {}
       ~node() {}
    
        C value;
    
        node<C>* parent;
        node<C>* first_child, last_child;
        node<C>* next_sibling, last_sibling;

    };

    /* Tree Type ******************************************************************/
    template<typename T>
    class tree {
    
    public:
        tree();
       ~tree();

        // iterator for preorder tree traversal
        class preorder_iterator : public std::iterator<std::forward_iterator_tag,T> {
        protected:
            node<T>* p;
            
        public:
            preorder_iterator             (const node<T>* x);
            preorder_iterator             (const preorder_iterator&);
            preorder_iterator& operator++ ();
            preorder_iterator& operator++ (int);
            bool               operator== (const preorder_iterator&);
            bool               operator!= (const preorder_iterator&);
            int&               operator*  ();
        };

        // iterator for inorder tree traversal
        class postorder_iterator : public std::iterator<std::forward_iterator_tag,T> {
        protected:
            node<T>* p;
        
        public:
            postorder_iterator             (const node<T>* x);
            postorder_iterator             (const postorder_iterator&);
            postorder_iterator& operator++ ();
            postorder_iterator& operator++ (int);
            bool                operator== (const postorder_iterator&);
            bool                operator!= (const postorder_iterator&);
            int&                operator*  ();
        };

        // functionality
        template<class C> void add_child     (const C&, const T&);
        template<class C> void add_sibling   (const C&, const T&);
        template<class C> void erase         (const C&);
        template<class C> void erase_subtree (const C&);

    protected:
        node<T>* origin;
        node<T>* front;
        node<T>* back;
    
    };

};

#if !defined(OXTREE_CPP)
#include "OxTree.cpp"
#endif

#endif















