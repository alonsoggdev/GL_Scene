//
//  Mesh.hpp
//  GL_Geometry
//
//  Created by Alonso García on 11/12/24.
//

#pragma once

#include <vector>

#include "glm.hpp"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "glad.h"

#include "Shader.hpp"

namespace udit
{
    class Mesh
    {
    private:
        enum
        {
            COORDINATES_VBO,
            COLORS_VBO,
            INDEXES_VBO,
            VBO_COUNT
        };
                
    protected:
        std::vector<glm::vec3> coordinates;
        std::vector<glm::vec3> colors;
        std::vector<GLuint> indices;

        void create_mesh(std::string mesh_name);
        
    private:
        GLuint vbo_ids[VBO_COUNT];
        GLuint vao_id;
        
        std::unique_ptr < udit::Shader > m_shader;

    public:

        Mesh();
        ~Mesh();
        void update();
        void render();
        void set_shader( std::unique_ptr < udit::Shader > shader );
        std::pair < GLint, GLint > get_shader_matrix_ids();

    };
}
