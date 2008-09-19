
#include <vector>


/* Node Type ******************************************************************/
template<typename T, std::size_t D>
class node {

public:
    typedef       typename std::vector<node<T,D>*>::iterator iterator;
    typedef const typename std::vector<node<T,D>*>::const_iterator const_iterator;
    typedef       T& reference;
    typedef const T& const_reference;
    typedef const std::size_t size_t;

    node() : children(D,0) {}
    node(const node<T,D>& _node) : children(D,0) { copy_constructor(_node); }
   ~node() { clear(); }

    inline iterator         begin()                         { return children.begin(); }
    inline const_iterator   begin()                   const { return children.begin(); }
    inline iterator         end()                           { return children.end();   }
    inline const_iterator   end()                     const { return children.end();   }
    inline node<T,D>*       operator[](size_t& index)       { return children[index];  }
    inline const node<T,D>* operator[](size_t& index) const { return children[index];  }
    inline std::size_t      size()                          { return D;                }
    
    T value;

private:
    std::vector<node<T,D>*> children;
    
    inline void copy_constructor(const node<T,D>& _node) {
        for (int i = 0; i < D; ++i)
            if (_node[i] != 0) children[i] = new node<T,D>(_node[i]);
    }

public:
    inline void assign(size_t& index, const T& val) {
        if (children[index])
            children[index]->clear();
        else
            children[index] = new node<T,D>();
        children[index]->value = val;
    }
    
    inline void clear() {
        for (int i = 0; i < D; ++i)
            if (children[i]) delete(children[i]);
    }
    
    inline bool leaf() {
        bool leaf = true;
        for (int i = 0; i < D; ++i)
            leaf = leaf && !children[i];
        return leaf;
    }

};


/* Tree Type ******************************************************************/
template<typename T, std::size_t D>
class tree {
  
public:
    

private:
    node<T, D> root;

};

