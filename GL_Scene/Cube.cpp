//
//  Cube.cpp
//  GL_Geometry
//
//  Created by Alonso García on 21/12/24.
//

#include <iostream>
#include <cmath>

#include "Cube.hpp"

using udit::Cube;

namespace udit
{
    Cube::Cube() : size(2.0f)
    {
        create_cube();
    }

    Cube::Cube(bool inverted)
    {
        create_cube(true);
    }

    Cube::Cube(float size) : size(size)
    {
        create_cube();
    }

    Cube::Cube(float size, bool inverted) : size(size)
    {
        create_cube(true);
    }

    void Cube::create_cube(bool inverted)
    {
        std::cout << "Creating cube" << std::endl;
        coordinates.clear();
        colors.clear();
        indices.clear();

        float half = size / 2.0f;

        glm::vec3 vertices[8] = {
            {-half, -half, half},
            { half, -half, half},
            { half,  half, half},
            {-half,  half, half},
            {-half, -half,  -half},
            { half, -half,  -half},
            { half,  half,  -half},
            {-half,  half,  -half}
        };
        
        glm::vec3 colores [12] =
        {
            { 0, 0 ,1 },
            { 0, 0 ,1 },
            { 0, 1 ,0 },
            { 0, 1 ,0 },
            { 1, 0 ,0 },
            { 1, 0 ,0 },
            { 1, 1 ,0 },
            { 1, 1 ,0 },
            { 0, 1 ,1 },
            { 0, 1 ,1 },
            { 1, 0 ,1 },
            { 1, 0 ,1 }
        };

        for (const auto& vertex : vertices) {
            coordinates.push_back(vertex);
        }
        
        std::vector<std::vector<unsigned int>> faces;
        
        if (!inverted)
        {
            faces =
            {
                {0, 1, 2}, {0, 2, 3},
                {4, 0, 3}, {4, 3, 7},
                {7, 5, 4}, {7, 6, 5},
                {1, 5, 6}, {1, 6, 2},
                {3, 2, 6}, {3, 6, 7},
                {5, 0, 4}, {5, 1, 0}
            };
            
        }
        else
        {
            faces =
            {
                {0, 2, 1}, {0, 3, 2},
                {4, 3, 0}, {4, 7, 3},
                {7, 4, 5}, {7, 5, 6},
                {1, 6, 5}, {1, 2, 6},
                {3, 6, 2}, {3, 7, 6},
                {5, 4, 0}, {5, 0, 1}
            };
        }
        
        int i = 0;

        for (const auto& face : faces) {
            indices.push_back(face[0]);
            indices.push_back(face[1]);
            indices.push_back(face[2]);
            
            colors.push_back(colores[i]);
            ++i;
        }
        
        
        
        create_mesh("Cube");
    }
}
