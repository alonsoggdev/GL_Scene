//
//  Cube.hpp
//  GL_Geometry
//
//  Created by Alonso García on 21/12/24.
//

#pragma once

#include "glad.h"

#include "Mesh.hpp"

namespace udit
{
    class Cube : public Mesh
    {
    private:
        float size;
    public:
        Cube();
        Cube(bool inverted);
        Cube(float size);
        Cube(float size, bool inverted);
    private:
        void create_cube(bool inverted = false);
    };
}
