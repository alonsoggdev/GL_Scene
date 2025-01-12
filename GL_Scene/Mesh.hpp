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
    enum class MeshType
    {
        MESH,
        TERRAIN,
        SKYBOX
    };

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
        
        MeshType m_mesh_type;
                
    protected:
        std::vector<glm::vec3> coordinates;
        std::vector<glm::vec3> colors;
        std::vector<GLuint> indices;
        
        GLsizei number_of_vertices;

        void create_mesh(std::string mesh_name = "");
        
    private:
        GLuint vbo_ids[VBO_COUNT];
        GLuint vao_id;
        glm::mat4 model_view_matrix;
        
        std::shared_ptr < udit::Shader > m_shader;

    public:

        Mesh();
        Mesh(std::string & path);
        ~Mesh();
        
        void translate(glm::vec3 translation);
        void rotate(glm::vec3 rotation, float angle);
        void scale(glm::vec3 scale);
        
        void update();
        void render(glm::mat4 view_matrix);
        void set_shader( std::shared_ptr < udit::Shader > shader );
        GLuint get_shader_program_id() const;
        std::vector < GLint > get_shader_matrix_ids();
        glm::mat4 get_model_view_matrix() const         { return model_view_matrix; }
        void set_model_view_matrix(glm::mat4 matrix)    { model_view_matrix = matrix; }
        
        void set_mesh_type(MeshType type) { m_mesh_type = type; }

    };
}
