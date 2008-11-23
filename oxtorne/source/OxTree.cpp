
#define OXTREE_CPP

#include "OxTree.h"
#include "OxAlgorithm.h"

#include <queue>

namespace oxtorne {

template<typename T>
tree<T>::tree() {
    this->front = new node<T>();
    this->back  = new node<T>();
}

template<typename T>
tree<T>::~tree() {
    delete this->front;
    delete this->back;
}

// *** preorder iteration starts here *************************************** //
template<typename T>
tree<T>::preorder_iterator::preorder_iterator(const node<T>* n) : p(n) {
}

template<typename T>
tree<T>::preorder_iterator::preorder_iterator(const preorder_iterator& n) : p(n.p) {
}

template<typename T>
preorder_iterator&
tree<T>::preorder_iterator::operator++() {
    
    assert(this->p != NULL);
    
    // move one step deeper into the tree
    if (this->p->first_child != NULL) {
        this->p = this->p->first_child;
        return *this;
    }
    
    // child is null, so check for next sibling
    if (this->p->next_sibling != NULL) {
        this->p = this->p->next_sibling;
        return *this;
    }
    
    // sibling also null so find the next node ...
    while (this->p->parent != NULL) {
        this->p = this->p->parent;
        if (this->p->next_sibling != NULL) {
            this->p = this->p->next_sibling;
            return *this;
        }
    }

    // seems we have reached the end of the tree
    // no remaining nodes to visit - set the pointer
    // to the invalid front pointer and stop
    this->p = this->front;
    return *this;
}

template<typename T>
preorder_iterator&
tree<T>::preorder_iterator::operator++(int) {
    preorder_iterator previous = *this;
    ++*this;
    return previous;
}

template<typename T>
bool
tree<T>::preorder_iterator::operator==(const preorder_iterator& n) {
    return n.p == p;
}

template<typename T>
bool
tree<T>::preorder_iterator::operator!=(const preorder_iterator& n) {
    return n.p != p;
}

template<typename T>
T&
tree<T>::preorder_iterator::operator*() {
    return *p;
}

// *** postorder iteration starts here ************************************** //
template<typename T>
tree<T>::postorder_iterator::postorder_iterator(const node<T>* n) : p(n) {
}

template<typename T>
tree<T>::postorder_iterator::postorder_iterator(const postorder_iterator& n) : p(n.p) {
}

template<typename T>
postorder_iterator&
tree<T>::postorder_iterator::operator++() {
    
    assert(this->p != NULL);
    
    // having reached a node that has no siblings
    // we go closer to the tree root
    if (this->p->next_sibling == NULL) {
        if (this->p->parent != NULL)
            this->p = this->p->parent;
        else
            this->p = this->front;
        return *this;
    }
    
    // we can now be absolutely sure that there
    // is a next sibling
    this->p = this->p->next_sibling;
    
    // go directly to the leaf (post order)
    while (this->p->first_child != NULL)
        this->p = this->p->first_child;

    // we should be at the next leaf by now
    return *this;
}

template<typename T>
postorder_iterator&
tree<T>::postorder_iterator::operator++(int) {
    postorder_iterator previous = *this;
    ++*this;
    return previous;
}

template<typename T>
bool
tree<T>::postorder_iterator::operator==(const postorder_iterator& n) {
    return n.p == p;
}

template<typename T>
bool
tree<T>::postorder_iterator::operator!=(const postorder_iterator& n) {
    return n.p != p;
}

template<typename T>
T&
tree<T>::postorder_iterator::operator*() {
    return *p;
}

// *** functional calls to the tree ***************************************** //
template<typename T, class C>
void
tree<T>::add_child(const C& c, const T& t) {
    node<T>* node = new node<T>();
}

template<class C> void add_sibling   (const C&, const T&);

template<class C> void erase         (const C&);

template<class C> void erase_subtree (const C&);

};