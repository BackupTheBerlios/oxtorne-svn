
#ifndef OXMEMORY_H
#define OXMEMORY_H

#include <cstddef>

template<typename T> class array {

public:
    array();
    array(const array<T>&);
   ~array();

    T&           operator[](const size_t& index);
    const T&     operator[](const size_t& index) const;
    T&           at        (const size_t& index);
    const T&     at        (const size_t& index) const;
    array&       operator= (const array<T>&);
    size_t       size      ();
    const size_t size      () const;
    size_t       real_size ();
    const size_t real_size () const;
    void         push_back (const T&);
    void         pop_back  ();
    void         clear     ();

private:
    T*     content;
    size_t entries;
    size_t entries_real;
};

template<typename T> T*   ox_alloc   (const size_t&);
template<typename T> T*   ox_realloc (const T*, const size_t&);
template<typename T> void ox_free    (const T*);

#if !defined(OXMEMORY_CPP)
#include "OxMemory.cpp"
#endif

#endif
