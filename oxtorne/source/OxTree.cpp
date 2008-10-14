
#define OXTREE_CPP

#include "OxTree.h"

namespace oxtorne {

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
/*template<typename T, std::size_t D>
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
}*/

template<typename T, std::size_t D>
octree<T,D>::octree(const box<T,D>& _box) {
    origin = new node();
    origin->value.first = _box;
}

template<typename T, std::size_t D>
octree<T,D>::~octree() {

}

//        void subdivide_node(const iterator_base&);
//        void merge_node    (const iterator_base&);

template<typename T> octree<T,3> make_octree(const mesh<T,3>& _mesh) {
    mesh<T,3>::v_iter _viter = _mesh.vertices_begin();
    mesh<T,3>::v_iter _vend  = _mesh.vertices_end();

    point<T,3> _min = make_point(T(INT_MAX), T(INT_MAX), T(INT_MAX));
    point<T,3> _max = make_point(T(INT_MIN), T(INT_MIN), T(INT_MIN));

    for(; _viter != _vend; ++_viter) {
        if ((*_viter)[0] < _min[0]) _min[0] = (*_viter)[0];
        if ((*_viter)[1] < _min[1]) _min[1] = (*_viter)[1];
        if ((*_viter)[2] < _min[2]) _min[2] = (*_viter)[2];
        if ((*_viter)[0] > _max[0]) _max[0] = (*_viter)[0];
        if ((*_viter)[1] > _max[1]) _max[1] = (*_viter)[1];
        if ((*_viter)[2] > _max[2]) _max[2] = (*_viter)[2];
    }
    
    std::cout << _min[0] << " " << _min[1] << " " << _min[2] << std::endl;
    std::cout << _max[0] << " " << _max[1] << " " << _max[2] << std::endl;

    octree<T,3> _tree(make_box(T(0.0), T(0.0), T(0.0), T(0.0), T(0.0), T(0.0)));
    



    std::cout << "Creating Octree" << std::endl;
    
    return _tree;
}

template<typename T> octree<T,3> make_octree(const std::vector<triangle<T,3> >& _triangle) {
    octree<T,3> _tree;
    return _tree;
}

};