
#ifndef OXALGORITHM_H
#define OXALGORITHM_H

#include "OxTree.h"

#include <vector>
#include <queue>

namespace oxtorne {

    template<typename T> std::vector<box<T, 3> >          subdivide_box (const box<T, 3>&, const int& = 0);
    template<typename T> std::set<typename mesh<T,3>::f_handle> intersecting_triangles (mesh<T,3>&, octree<T,3>&, const line<T,3>&, const T& = T(0.0));
    template<typename T> std::set<typename mesh<T,3>::f_handle> intersecting_triangles (mesh<T,3>&, octree<T,3>&, const ray<T,3>&, const T& = T(0.0));

};

#if !defined(OXALGORITHM_CPP)
#include "OxAlgorithm.cpp"
#endif

#endif

