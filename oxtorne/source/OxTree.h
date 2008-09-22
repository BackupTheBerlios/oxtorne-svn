
#include <vector>


/* Node Type ******************************************************************/
template<typename T, std::size_t D>
class node {

public:
    typedef       T& reference;
    typedef const T& const_reference;

    node() { for (int i = 0; i < D; ++i ) nodes[i] = NULL; }
   ~node() { for (int i = 0; i < D; ++i ) if (nodes[i]) delete nodes[i]; }

    inline node<T,D>*       begin()                         { return children[0];     }
    inline const node<T,D>* begin()                   const { return children[0];     }
    inline node<T,D>*       end()                           { return children[D - 1]; }
    inline const node<T,D>* end()                     const { return children[D - 1]; }
    inline node<T,D>*       operator[](size_t& index)       { return children[index]; }
    inline const node<T,D>* operator[](size_t& index) const { return children[index]; }
    inline std::size_t      size()                          { return D;               }
    
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


/* Tree Type ******************************************************************/
template<typename T, std::size_t D>
class tree {
  
public:
    

private:
    node<T, D> root;

};

