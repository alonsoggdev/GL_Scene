//
//  Shader.hpp
//  GL_Geometry
//
//  Created by Alonso García on 11/12/24.
//

#pragma once

#include <iostream>

#include "glad.h"

#include "Texture.hpp"

namespace udit
{
    enum class ShaderType
    {
        SKYBOX,
        GEOMETRY,
        SINGLE_TEXTURE,
        TERRAIN,
        DEFAULT
    };

    class Shader
    {
    private:
        GLuint program_id;
        ShaderType m_type;
        std::string m_name;
        
        std::string absolute_path = "/Users/alonsoggdev/UDIT/Asignaturas/Programacion_Grafica/GL_Scene/GL_Scene/";
        
        std::string m_vertex_default_source = absolute_path + "Shader_Default_Vertex.glsl";
        std::string m_fragment_default_source = absolute_path + "Shader_Default_Fragment.glsl";
        
        std::string m_vertex_source;
        std::string m_fragment_source;
        
        GLint  model_view_matrix_id;
        GLint  projection_matrix_id;
        GLint  normal_matrix_id;
        
        static const std::string    default_vertex_shader_code;
        static const std::string    default_fragment_shader_code;
        
        std::vector <std::shared_ptr<Texture>> textures;
    public:
        Shader();
        Shader(ShaderType type, const std::string & vertex_source, const std::string & fragment_source, const std::string & name);
        static std::shared_ptr < Shader > make_shader(
            udit::ShaderType type = udit::ShaderType::DEFAULT,
            const std::string & vertex_shader = "",
            const std::string & fragment_shader = "",
            const std::vector<std::string> & texture_paths = {""},
            const std::string & name = ""
                                                      );
        GLuint compile_shaders(const char * vertex_shader_code, const char * fragment_shader_code);
        
        GLint get_model_view_matrix_id() { return model_view_matrix_id; }
        GLint get_projection_matrix_id() { return projection_matrix_id; }
        GLint get_normal_matrix_id() { return normal_matrix_id; }
        
        GLuint get_program_id() const { return program_id; }

        void set_texture(const std::shared_ptr<Texture> & texture);
        void use() const;
        
        void set_texture_scale(float scale);
        
        bool has_textures() { return !textures.empty(); }
        
        void set_name(const std::string & name) { m_name = name; }
        std::string get_name() { return m_name; }

    private:
        
        void show_compilation_error(GLuint shader_id);
        void show_linkage_error(GLuint program_id);
    };
}
