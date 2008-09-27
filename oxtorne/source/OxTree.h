
#include <vector>

/* Node Type ******************************************************************/
template<typename T, std::size_t D>
class node_ {

public:
    
    node_() { for (int i = 0; i < D; ++i )     nodes[i] = NULL;           }
   ~node_() { for (int i = 0; i < D; ++i ) if (nodes[i]) delete nodes[i]; }

    inline node_<T,D>*       front     ()                               { return nodes[0];     }
    inline const node_<T,D>* front     ()                         const { return nodes[0];     }
    inline node_<T,D>*       back      ()                               { return nodes[D - 1]; }
    inline const node_<T,D>* back      ()                         const { return nodes[D - 1]; }
    inline node_<T,D>*       operator[](const std::size_t& index)       { return nodes[index]; }
    inline const node_<T,D>* operator[](const std::size_t& index) const { return nodes[index]; }
    inline std::size_t       size      ()                               { return D;            }

    T value;

private:
    node_<T,D>* nodes[D];

};

/* Tree Type ******************************************************************/
template<typename T, std::size_t D>
class tree {
    
public:

    typedef       node_<T,D> node;
    typedef const node_<T,D> const_node;

    tree() {}
   ~tree() {}

    inline node&       root ();
    inline const_node& root () const;
    inline node&       child(const node&, const std::size_t&);
    inline const_node& child(const node&, const std::size_t&) const;
    
    inline node&       next_sibling(const node&);
    inline const_node& next_sibling(const node&) const;
    inline node&       prev_sibling(const node&);
    inline const_node& prev_sibling(const node&) const;
    
    inline bool        has_next_sibling(const node&);
    inline bool        has_prev_sibling(const node&);
    
    inline bool        leaf (const node&);

private:
    node* origin;
    
};
