
#include "OxGeometry.h"

namespace oxtorne {
namespace mesh {

    /* Forward declarations ***************************************************/ 
    template <typename T, std::size_t D> class vertex;
    template <typename T, std::size_t D> class face;
    template <typename T, std::size_t D> class half_edge;

    /* Mesh Component declarations ********************************************/
    template<typename T, std::size_t D>
    class vertex : public point<T,D> {
    };

    template<typename T, std::size_t D>
    class face {
        half_edge<T,D>* edge;
    };

    template<typename T, std::size_t D>
    class half_edge {
    
    public:
        face<T,D>* face;
        vertex<T,D>* vertex;
        half_edge<T,D>* opposite;
        half_edge<T,D>* next;

    };
    
    /* Mesh type itself *******************************************************/
    template<typename T, std::size_t D>
    class mesh {
    
    public:
        
        mesh() : faces(0), vertices(0), half_edges(0) {}
       ~mesh() {}
    
        void add_face();
        void add_vertex();
        void add_halfedge();
    
    protected:
        face<T,D>* faces;
        vertex<T,D>* vertices;
        half_edge<T,D>* half_edges;

    };

}; // namespace mesh
}; // namespace oxtorne
