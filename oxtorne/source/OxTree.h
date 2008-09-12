
#include <vector>


/* Node Type ******************************************************************/
template<typename T, std::size_t D>
class node {

public:
    typedef       typename std::vector<node<T,D>*>::iterator iterator;
    typedef const typename std::vector<node<T,D>*>::const_iterator const_iterator;
    typedef       typename T& reference;
    typedef const typename T& const_reference;

    node() : children(D) {}
   ~node() {}

    inline iterator         begin()                                    { return children.begin(); }
    inline const_iterator   begin()                              const { return children.begin(); }
    inline iterator         end()                                      { return children.end();   }
    inline const_iterator   end()                                const { return children.end();   }
    inline reference&       operator[](const std::size_t& index)       { return children[index];  }
    inline const_reference& operator[](const std::size_t& index) const { return children[index];  }
    inline std::size_t      size()                                     { return D;                }

    T value;

private:
    std::vector<node<T,D>*> children;

};


/* Tree Type ******************************************************************/
template<typename T, std::size_t D>
class tree {
  
public:
    

private:
    node<T, D> root;

};

