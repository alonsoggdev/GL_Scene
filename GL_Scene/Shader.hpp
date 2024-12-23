//
//  Shader.hpp
//  GL_Geometry
//
//  Created by Alonso García on 11/12/24.
//

#pragma once

#include <iostream>

#include "glad.h"

namespace udit
{
    enum class ShaderType
    {
        SKYBOX,
        GEOMETRY,
        DEFAULT
    };

    class Shader
    {
    private:
        GLuint program_id;
        ShaderType m_type;
        
        std::string absolute_path = "/Users/alonsoggdev/UDIT/Asignaturas/Programacion_Grafica/GL_Scene/GL_Scene/";
        
        std::string m_vertex_source;
        std::string m_fragment_source;
        
        GLint  model_view_matrix_id;
        GLint  projection_matrix_id;
        
        static const std::string    default_vertex_shader_code;
        static const std::string    default_fragment_shader_code;
    public:
        Shader();
        Shader(ShaderType type, const std::string & vertex_source, const std::string & fragment_source);
        GLuint compile_shaders(const char * vertex_shader_code, const char * fragment_shader_code);
        
        GLint get_model_view_matrix_id() { return model_view_matrix_id; }
        GLint get_projection_matrix_id() { return projection_matrix_id; }
        
        GLuint get_program_id() const { return program_id; }
    private:
        void show_compilation_error(GLuint shader_id);
        void show_linkage_error(GLuint program_id);
    };
}
