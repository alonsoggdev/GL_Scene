//
//  Plane.cpp
//  GL_Geometry
//
//  Created by Alonso García on 11/12/24.
//

#include <iostream>

#include "Plane.hpp"

using udit::Plane;

namespace udit
{

    Plane::Plane() : width(5.0f), height(5.0f), columns (5), rows (5)
    {
        create_plane();
    }

    Plane::Plane(float width, float height, unsigned columns, unsigned rows) : width(width), height(height), columns (columns), rows (rows)
    {
        create_plane();
    }

    void Plane::create_plane()
    {
        coordinates.clear();
        colors.clear();
        indices.clear();
        
        coordinates.reserve((columns + 1) * (rows + 1));
        
        glm::vec3 vertex = glm::vec3(- width / 2.0f, -height / 2.0f, 0);
        
        float tile_width = width / float(columns);
        float tile_height = height / float(rows);
                
        for (unsigned i = 0; i <= rows; ++i)
        {
            for (unsigned j = 0; j <= columns; ++j)
            {
                coordinates.push_back(vertex);
                glm::vec3 color = glm::vec3(float(j) / float(columns), float(i) / float(rows), 1.0f);
                colors.push_back(color);
                vertex.x += tile_width;
            }
            vertex.x = - width / 2.0f;
            vertex.y += tile_height;
        }
        
        //std::cout << "Vertex amount: " << coordinates.size() << std::endl;
        
        for (unsigned i = 0; i < rows; ++i)
        {
            for (unsigned j = 0; j < columns; ++j)
            {
                unsigned top_left       = i * (columns + 1) + j;
                unsigned bottom_left    = (i + 1) * (columns + 1) + j;
                unsigned top_right      = top_left +  1;
                unsigned bottom_right   = bottom_left + 1;
                
                indices.push_back(top_left);
                indices.push_back(bottom_left);
                indices.push_back(top_right);
                
                indices.push_back(top_right);
                indices.push_back(bottom_left);
                indices.push_back(bottom_right);
                
                // std::cout << top_left << ", " << bottom_left << ", " << top_right << std::endl << top_right << ", " << bottom_left << ", " << bottom_right << std::endl;
            }
        }
        create_mesh("Plane");
    }
}
