
#define OXTREE_CPP

#include "OxTree.h"

/* Function Implementations for iterator_base *********************************/
template<typename T, std::size_t D>
tree<T,D>::iterator_base::iterator_base() : node(0) {
}

template<typename T, std::size_t D>
tree<T,D>::iterator_base::iterator_base(const_node* _node) {
    value = _node;
}

template<typename T, std::size_t D>
T&
tree<T,D>::iterator_base::operator* () const {
    return value->value;
}

template<typename T, std::size_t D>
T*
tree<T,D>::iterator_base::operator-> () const {
    return &value->value;
}

template<typename T, std::size_t D>
bool
tree<T,D>::iterator_base::operator==(const iterator_base& _iter) const {
    return this->value == _iter->value;
}

template<typename T, std::size_t D>
bool
tree<T,D>::iterator_base::operator!=(const iterator_base& _iter) const {
    return this->value != _iter->value;
}

/* Function Implementation for sibling_iterator *******************************/
template<typename T, std::size_t D>
tree<T,D>::sibling_iterator::sibling_iterator() : node(0) {
}

template<typename T, std::size_t D>
tree<T,D>::sibling_iterator::sibling_iterator(const_node* _node) {
    this->value = _node;
}

template<typename T, std::size_t D>
tree<T,D>::sibling_iterator::sibling_iterator(const iterator_base& _iter) : iterator_base(_iter) {
    this->value = _iter->value;
}

template<typename T, std::size_t D>
typename tree<T,D>::sibling_iterator&
tree<T,D>::sibling_iterator::operator++() {
    this->value++;
    return *this;
}

template<typename T, std::size_t D>
typename tree<T,D>::sibling_iterator&
tree<T,D>::sibling_iterator::operator--() {
    this->value--;
    return *this;
}

template<typename T, std::size_t D>
typename tree<T,D>::sibling_iterator
tree<T,D>::sibling_iterator::operator++(const int) {
    sibling_iterator _iter = *this;
    ++(*this);
    return _iter;
}

template<typename T, std::size_t D>
typename tree<T,D>::sibling_iterator
tree<T,D>::sibling_iterator::operator--(const int) {
    this->value--;
    return *this;
}

template<typename T, std::size_t D>
typename tree<T,D>::sibling_iterator&
tree<T,D>::sibling_iterator::operator+=(const std::size_t& _increment) {
    this->value += _increment;
    return (*this);
}

template<typename T, std::size_t D>
typename tree<T,D>::sibling_iterator&
tree<T,D>::sibling_iterator::operator-=(const std::size_t& _decrement) {
    this->value -= _decrement;
    return (*this);
}

/* Function Implementation for breadth_first_iterator *********************/
template<typename T, std::size_t D>
tree<T,D>::breadth_first_iterator::breadth_first_iterator() : node(0) {
}

template<typename T, std::size_t D>
tree<T,D>::breadth_first_iterator::breadth_first_iterator(const_node* _node) {
    this->value = _node;
}

template<typename T, std::size_t D>
tree<T,D>::breadth_first_iterator::breadth_first_iterator(const iterator_base& _iter) : iterator_base(_iter) {
    this->value = _iter->value;
}

template<typename T, std::size_t D>
typename tree<T,D>::breadth_first_iterator&
tree<T,D>::breadth_first_iterator::operator++() {
    // TODO: write code here - tomorrow!!
}
