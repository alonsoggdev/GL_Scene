//
//  Mesh.cpp
//  GL_Geometry
//
//  Created by Alonso García on 11/12/24.
//

#include <iostream>

#include "Mesh.hpp"

using udit::Mesh;

namespace udit
{
    /**
     *@brief Constructor por defecto
     */
    Mesh::Mesh()
    {
        
    }
    
    /**
     *@brief Crea una malla utilizando las coordenadas, colores e indices de la propia clase
     *
     *@param mesh_name Nombre de la malla
     */
    void Mesh::create_mesh(std::string mesh_name)
    {
        // std::cout << "Creating Mesh: " << mesh_name << std::endl;
        glGenBuffers(VBO_COUNT, vbo_ids);
        glGenVertexArrays(1, &vao_id);
        
        glBindVertexArray(vao_id);
        
        glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[COORDINATES_VBO]);
        glBufferData(GL_ARRAY_BUFFER, coordinates.size() * sizeof(glm::vec3), coordinates.data(), GL_STATIC_DRAW);
        
        glEnableVertexAttribArray (0);
        glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 0, 0);


        glBindBuffer (GL_ARRAY_BUFFER, vbo_ids[COLORS_VBO]);
        glBufferData (GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);

        glEnableVertexAttribArray (1);
        glVertexAttribPointer (1, 3, GL_FLOAT, GL_FALSE, 0, 0);


        glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, vbo_ids[INDEXES_VBO]);
        glBufferData (GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);

        glBindVertexArray (0);
        
        /*
        for (size_t i = 0; i < coordinates.size(); ++i) {
            const glm::vec3& coord = coordinates[i];
            std::cout << "(" << coord.x << ", " << coord.y << ", " << coord.z << ")";
            if (i != coordinates.size() - 1) {
                std::cout << ", ";
            }
        }

        std::cout << std::endl;
         */
    }

    /**
     *@brief Destructor de la clase
     */
    Mesh::~Mesh()
    {
        glDeleteVertexArrays (1, &vao_id);
        glDeleteBuffers      (VBO_COUNT, vbo_ids);
    }
    
    /**
     *@brief Función de actualizacion de la malla en el bucle principal
     */
    void Mesh::update()
    {
    }

    /**
     *@brief Función de renderizado de la malla en el bucle principal
     */
    void Mesh::render()
    {
        // std::cout << "Rendering mesh..." << std::endl;
        glBindVertexArray (vao_id);
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
        glBindVertexArray (0);
    }

    void Mesh::set_shader( std::unique_ptr < udit::Shader > shader)
    {
        if (shader != nullptr)
        {
            m_shader = std::move(shader);
        }
    }

    std::pair < GLint, GLint > Mesh::get_shader_matrix_ids()
    {
        return std::make_pair(m_shader->get_model_view_matrix_id(), m_shader->get_projection_matrix_id());
    }
}
