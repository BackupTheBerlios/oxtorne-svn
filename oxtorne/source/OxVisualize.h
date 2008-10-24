
#ifndef OXVISUALIZE_H
#define OXVISUALIZE_H

#include <GL/glut.h>

#include "OxGeometry.h"
#include "OxMesh.h"

namespace oxtorne {

    template<typename T> GLuint wire (const box<T,3>&);
    template<typename T> GLuint wire (const line<T,3>&, const std::size_t& = 0);
    template<typename T> GLuint wire (const ray<T,3>&, const std::size_t& = 0);
    template<typename T> GLuint wire (const sphere<T,3>&);

    template<typename T> GLuint solid (mesh<T,3>&);
    template<typename T> GLuint solid (const point<T,3>&, const std::size_t& = 0);
    template<typename T> GLuint solid (const sphere<T,3>&);
    template<typename T> GLuint solid (const triangle<T,3>&, const std::size_t& = 0);

    template<typename T> void   coordinate_system (const T&);
    template<typename T> GLuint mesh_white(mesh<T,3>&);

};

const unsigned int color_table_size = 54;
const unsigned int color_table[54][3] = {
    {0,   0,   0  },
    // {255, 255, 255},
    // {255, 0,   0  },
    {0,   255, 0  },
    {0,   0,   255},
    {255, 255, 0  },
    {255, 0,   255},
    {0,   255, 255},
    {128, 0,   0  },
    {0,   128, 0  },
    {0,   0,   128},
    {128, 128, 0  },
    {128, 0,   128},
    {0,   128, 128},
    {192, 192, 192},
    {128, 128, 128},
    {153, 153, 255},
    {153, 51,  102},
    {255, 255, 204},
    {204, 255, 255},
    {102, 0,   102},
    {255, 128, 128},
    {0,   102, 204},
    {204, 204, 255},
    {0,   0,   128},
    {255, 0,   255},
    {255, 255, 0  },
    {0,   255, 255},
    {128, 0,   128},
    {128, 0,   0  },
    {0,   128, 128},
    {0,   0,   255},
    {0,   204, 255},
    {204, 255, 255},
    {204, 255, 204},
    {255, 255, 153},
    {153, 204, 255},
    {255, 153, 204},
    {204, 153, 255},
    {255, 204, 153},
    {51,  102, 255},
    {51,  204, 204},
    {153, 204, 0  },
    {255, 204, 0  },
    {255, 153, 0  },
    {255, 102, 0  },
    {102, 102, 153},
    {150, 150, 150},
    {0,   51,  102},
    {51,  153, 102},
    {0,   51,  0  },
    {51,  51,  0  },
    {153, 51,  0  },
    {153, 51,  102},
    {51,  51,  153},
    {51,  51,  51 }
};

#if !defined(OXVISUALIZE_CPP)
#include "OxVisualize.cpp"
#endif

#endif
