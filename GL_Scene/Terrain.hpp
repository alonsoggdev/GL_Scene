//
//  Terrain.hpp
//  GL_Scene
//
//  Created by Alonso García on 26/12/24.
//

#include <glad.h>

#include "Mesh.hpp"

class Terrain : public udit::Mesh
{
private:

    unsigned int grid_size;
    float        cell_size;
    
private:
    
    void create_terrain();

public:

    Terrain(unsigned int grid_size, float cell_size);
};
