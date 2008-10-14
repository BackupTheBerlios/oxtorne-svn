
#define OXTREE_CPP

#include "OxTree.h"

#include <queue>

namespace oxtorne {

/* Implementations for the leaf *******************************************/

template<typename C, std::size_t D>
bool
node_<C,D>::leaf() {
    for (int i = 0; i < D; ++i)
        if (nodes[i] != 0)
            return false;
    return true;
}

template<typename C, std::size_t D>
std::size_t
node_<C,D>::depth () {
    if (this->parent != 0)
        return this->parent->depth() + 1;
    else
        return 0;
}

/* Implementations for the octree *****************************************/
template<typename T, std::size_t D>
octree<T,D>::octree(const box<T,D>& _box) {
    origin = new node();
    origin->value.first = _box;
}

template<typename T, std::size_t D>
octree<T,D>::~octree() {

}

template<typename T, std::size_t D>
void
octree<T,D>::subdivide_node (node* _node) {
    
    std::vector<box<T,3> > _boxes = subdivide_box(_node->value.first);
    
    for (int i = 0; i < 8; ++i) {
        _node->at(i) = new node();
        _node->at(i)->parent = _node;
        _node->at(i)->value.first = _boxes[i];
    }
}

template<typename T, std::size_t D>
void
octree<T,D>::add_face (mesh<T,3>& _mesh, const typename mesh<T,3>::f_handle& _face) {
    triangle<T,3> _triangle;

    mesh<T,3>::fviter fv_iter = _mesh.face_vertex_begin(_face);
    _triangle[0] = (*fv_iter); fv_iter++;
    _triangle[1] = (*fv_iter); fv_iter++;
    _triangle[2] = (*fv_iter);

    // build a queue to remember nodes
    typedef octree<T,3>::node node;
    std::queue<node*> _nodes;

    // start iterating
    _nodes.push(root());

    while(!_nodes.empty()) {
        // prepare next node
        node* _next = _nodes.front();
        _nodes.pop();

        // triangle does not intersect the box
        if (!intersect(_next->value.first, _triangle))
            continue;
        
        _next->value.second.push_back(_face);

        // node is a leaf
        if (_next->leaf()) {
            _next->value.second.push_back(_face);
            continue;
        }

        // node is an inner node
        for (std::size_t i = 0; i < _next->size(); ++i)
            _nodes.push(_next->at(i));
    }
}

template<typename T> octree<T,3> make_octree(mesh<T,3>& _mesh, const std::size_t& _depth) {
    mesh<T,3>::viter _viter = _mesh.vertices_begin();
    mesh<T,3>::viter _vend  = _mesh.vertices_end();

    point<T,3> _min = make_point(T(INT_MAX), T(INT_MAX), T(INT_MAX));
    point<T,3> _max = make_point(T(INT_MIN), T(INT_MIN), T(INT_MIN));

    for(; _viter != _vend; ++_viter) {
        if ((**_viter)[0] < _min[0]) _min[0] = (**_viter)[0];
        if ((**_viter)[1] < _min[1]) _min[1] = (**_viter)[1];
        if ((**_viter)[2] < _min[2]) _min[2] = (**_viter)[2];
        if ((**_viter)[0] > _max[0]) _max[0] = (**_viter)[0];
        if ((**_viter)[1] > _max[1]) _max[1] = (**_viter)[1];
        if ((**_viter)[2] > _max[2]) _max[2] = (**_viter)[2];
    }

    // build octree
    octree<T,3> _tree(make_box(_min, _max));
    
    // build a queue to remember nodes
    typedef octree<T,3>::node node;
    std::queue<node*> _nodes;

    // start iterating
    _nodes.push(_tree.root());

    while(!_nodes.empty()) {
        // prepare next node
        node* _next = _nodes.front();
        _nodes.pop();

        // check depth limit
        // std::cout << _next->depth() << std::endl;
        if (_next->depth() >= _depth)
            continue;

        // subdivide the node
        _tree.subdivide_node(_next);
        
        // remember children
        for (std::size_t i = 0; i < 8; ++i)
            _nodes.push(_next->at(i));
    }

    // the tree has been created - now insert all faces
    mesh<T,3>::fiter f_iter = _mesh.faces_begin();
    
    // iterator over the faces
    for (; f_iter != _mesh.faces_end(); ++f_iter)
        _tree.add_face(_mesh, *f_iter);

    // return base class
    return _tree;
}

};