//
//  Plane.hpp
//  GL_Geometry
//
//  Created by Alonso García on 11/12/24.
//

#pragma once

#include "glad.h"

#include "Mesh.hpp"

namespace udit
{
    class Plane : public Mesh
    {
    private:
        float width;
        float height;
        unsigned columns;
        unsigned rows;
    public:
        Plane();
        Plane(float size);
        Plane(float width, float height, unsigned columns, unsigned rows);
    private:
        void create_plane();
    };
}
