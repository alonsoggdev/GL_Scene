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
        BASIC,
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
            NORMALS_VBO,
            INDEXES_VBO,
            TEXTURE_UV_VBO,
            VBO_COUNT
        };
        
        MeshType m_mesh_type;
                
    protected:
        std::vector<glm::vec3> coordinates;
        std::vector<glm::vec3> colors;
        std::vector<glm::vec3> normals;
        std::vector<GLuint> indices;
        std::vector<glm::vec2> texture_uvs;
        
        GLsizei number_of_vertices;

        void create_mesh(std::string mesh_name = "");
        
    private:
        GLuint vbo_ids[VBO_COUNT];
        GLuint vao_id;
        glm::mat4 model_view_matrix;
        glm::mat4 normal_matrix;
        
        std::shared_ptr < udit::Shader > m_shader;

    public:
        Mesh();
        Mesh(std::string & path);
        static std::shared_ptr <Mesh> make_mesh(MeshType type, const std::string &path = "");
        virtual ~Mesh();
        
        virtual void translate(glm::vec3 translation);
        virtual void rotate(glm::vec3 rotation, float angle);
        virtual void scale(glm::vec3 scale);
        
        virtual void update();
        virtual void render(glm::mat4 view_matrix);
        virtual void resize(glm::mat4 projection_matrix);
        virtual void set_shader( std::shared_ptr < udit::Shader > shader );
        GLuint get_shader_program_id() const;
        std::vector < GLint > get_shader_matrix_ids();
        glm::mat4 get_model_view_matrix() const         { return model_view_matrix; }
        void set_model_view_matrix(glm::mat4 matrix)    { model_view_matrix = matrix; }
        
        void set_mesh_type(MeshType type) { m_mesh_type = type; }

    };
}
