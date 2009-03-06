
#define OXMEMORY_CPP

#include <stdio.h>

#include "OxMemory.h"

template<typename T> array<T>::array() { 
    this->entries      = 0;
    this->entries_real = 1;
    this->content      = ox_alloc<T>(this->entries_real);
}

template<typename T> array<T>::array(const array<T>& _other) {
    this->entries      = _other.entries;
    this->entries_real = _other.entries_real;
    this->content      = ox_alloc<T>(this->entries_real);
    
    for (size_t i = 0; i < _other.size(); ++i)
        this->content[i] = _other[i];
}

template<typename T> array<T>::~array() {
    ox_free(this->content);
}

template<typename T> T& array<T>::operator[](const size_t& index) {
    return this->content[index];
}

template<typename T> const T& array<T>::operator[](const size_t& index) const {
    return this->content[index];
}

template<typename T> T& array<T>::at(const size_t& index) {
    return this->content[index];
}

template<typename T> const T& array<T>::at(const size_t& index) const {
    return this->content[index];
}

template<typename T> array<T>& array<T>::operator=(const array<T>& _other) {
    ox_free(this->content);

    this->entries      = _other.entries;
    this->entries_real = _other.entries_real;
    this->content      = ox_alloc<T>(this->entries_real);
    
    for (size_t i = 0; i < _other.size(); ++i)
        this->content[i] = _other[i];

    return *this;
}

template<typename T> size_t array<T>::size() {
    return this->entries;
}

template<typename T> const size_t array<T>::size() const {
    return this->entries;
}

template<typename T> size_t array<T>::real_size() {
    return this->entries_real;
}

template<typename T> const size_t array<T>::real_size() const {
    return this->entries_real;
}

template<typename T> void array<T>::push_back(const T& _element) {
    this->entries = this->entries + 1;
    
    // grow the array because more space is required
    if (this->entries > this->entries_real) {
        this->entries_real = this->entries_real * 2;
        this->content = ox_realloc(this->content, this->entries_real);
    }

    this->content[this->entries - 1] = _element;
}

template<typename T> void array<T>::pop_back() {
    this->entries = this->entries - 1;

    // shrink the array if space is not required
    if (this->entries < this->entries_real / 2 && this->entries_real > 2) {
        this->entries_real = this->entries_real / 2;
        this->content = ox_realloc(this->content, this->entries_real);
    }
}

template<typename T> void array<T>::clear() {
    ox_free(this->content);

    this->entries = 0;
    this->entries_real = 1;
    this->content = ox_alloc<T>(this->entries_real);
}

template<typename T> T* ox_alloc (const size_t& _size) {

    T* mem = (T*) NULL;
    
    if (_size == 0)
        fprintf(stderr, "Warning: allocating 0 bytes\n");
    
    mem = (T*) malloc (_size * sizeof(T));

    if (mem == (T*) NULL)
        fprintf(stderr, "Out of memory while requesting %d bytes\n", (int) _size);
    
    return mem;    
}

template<typename T> void ox_free (const T* _pointer) {

    if (!_pointer) {
        fprintf (stderr, "Warning: cannot free null pointer\n");
        return;
    }

    free ((void*) _pointer);
}

template<typename T> T* ox_realloc (const T* _pointer, const size_t& _size) {
    T* _newpointer;

    if (!_pointer) {
        return ox_alloc<T>(_size);
    } else {
        _newpointer = (T*) realloc ((void*) _pointer, _size * sizeof(T));
        if (!_newpointer)
            fprintf (stderr, "Out of memory while growing to %d bytes\n", (int) _size);
        return _newpointer;
    }
}
