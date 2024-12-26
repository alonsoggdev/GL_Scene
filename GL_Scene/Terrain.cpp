//
//  Terrain.cpp
//  GL_Scene
//
//  Created by Alonso García on 26/12/24.
//

#include "Terrain.hpp"
#include <glm.hpp>
#include <vector>

using glm::vec3;
using std::vector;

Terrain::Terrain(unsigned int grid_size, float cell_size)
: grid_size(grid_size), cell_size(cell_size)
{
    create_terrain();
}

void Terrain::create_terrain()
{
    // Coordenadas iniciales (parte inferior izquierda de la cuadrícula)
    float x_start = -0.5f * grid_size * cell_size;
    float z_start = -0.5f * grid_size * cell_size;

    float x_step = cell_size;
    float z_step = cell_size;

    float x = x_start;
    float z = z_start;

    // Generar vértices y sus índices
    for (unsigned int j = 0; j < grid_size; ++j, z += z_step)
    {
        for (unsigned int i = 0; i < grid_size; ++i, x += x_step)
        {
            // Guardar las coordenadas del vértice (Y = 0, será ajustado en el shader)
            coordinates.emplace_back(x, 0.0f, z);
            colors.emplace_back(0.5, 0.5f, 0.5f);

            // Generar índices para los triángulos
            if (j < grid_size - 1 && i < grid_size - 1)
            {
                unsigned int top_left = j * grid_size + i;
                unsigned int top_right = top_left + 1;
                unsigned int bottom_left = (j + 1) * grid_size + i;
                unsigned int bottom_right = bottom_left + 1;

                // Primer triángulo
                indices.push_back(top_left);
                indices.push_back(bottom_left);
                indices.push_back(top_right);

                // Segundo triángulo
                indices.push_back(top_right);
                indices.push_back(bottom_left);
                indices.push_back(bottom_right);
            }
        }
        // Cambiar la dirección en X para un patrón en zigzag
        x += x_step = -x_step;
    }
    create_mesh("Terrain");
}
