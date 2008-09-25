
#include <vector>

/* Node Type ******************************************************************/
template<typename T, std::size_t D>
class node {

public:
    typedef       T& reference;
    typedef const T& const_reference;

    class iterator : public std::iterator< std::bidirectional_iterator_tag, node<T,D> > {
    public:
        iterator() {}
       ~iterator() {}

        inline iterator&  operator++()                      { ++node; return *this;      }
        inline iterator   operator++(int)                   { iterator last = *this; ++*this; return last; }
        inline iterator&  operator--()                      { --node; return *this;      }
        inline iterator   operator--(int)                   { iterator last = *this; --*this; return last; }
        inline bool       operator==(const iterator& other) { return node == other.node; }
        inline bool       operator!=(const iterator& other) { return node != other.node; }
        inline node<T,D>& operator* ()                      { return **node;             }
        inline node<T,D>* operator->()                      { return  *node;             }

        node<T,D>** node;
    };

    class const_iterator : public std::iterator< std::bidirectional_iterator_tag, node<T,D> > {
    public:
        const_iterator() {}
       ~const_iterator() {}

        inline bool       operator==(const_iterator& other) { return node == other.node; }
        inline bool       operator!=(const_iterator& other) { return node != other.node; }
        inline node<T,D>& operator* ()                      { return **node;             }
        inline node<T,D>* operator->()                      { return  *node;             }

        node<T,D>** node;
    };

    node() { for (int i = 0; i < D; ++i ) nodes[i] = NULL; }
   ~node() { for (int i = 0; i < D; ++i ) if (nodes[i]) delete nodes[i]; }

    inline node<T,D>*       front     ()                               { return nodes[0];      }
    inline const node<T,D>* front     ()                         const { return nodes[0];      }
    inline node<T,D>*       back      ()                               { return nodes[D - 1];  }
    inline const node<T,D>* back      ()                         const { return nodes[D - 1];  }
    inline node<T,D>*       operator[](const std::size_t& index)       { return nodes[index];  }
    inline const node<T,D>* operator[](const std::size_t& index) const { return nodes[index];  }
    inline std::size_t      size      ()                               { return D;             }

    inline iterator         begin     ()                               { iterator iter; iter.node = nodes;     return iter; }
    inline iterator         end       ()                               { iterator iter; iter.node = nodes + D; return iter; }

    T* value;

private:
    
    node<T,D>* nodes[D];

public:
    inline bool leaf() {
        for (int i = 0; i < D; ++i)
            if (nodes[i]) return false;
        return true;
    }

};
