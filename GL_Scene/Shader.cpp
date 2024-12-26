//
//  Shader.cpp
//  GL_Geometry
//
//  Created by Alonso García on 11/12/24.
//

#include <sstream>
#include <fstream>

#include "Shader.hpp"

namespace udit
{
    const std::string Shader::default_vertex_shader_code =
        "#version 330\n"
        ""
        "uniform mat4 model_view_matrix;"
        "uniform mat4 projection_matrix;"
        ""
        "layout (location = 0) in vec3 vertex_coordinates;"
        "layout (location = 1) in vec3 vertex_color;"
        ""
        "out vec3 front_color;"
        ""
        "void main()"
        "{"
        "   gl_Position = projection_matrix * model_view_matrix * vec4(vertex_coordinates, 1.0);"
        "   front_color = vertex_color;"
        "}";

    const std::string Shader::default_fragment_shader_code =
        "#version 330\n"
        ""
        "in  vec3 front_color;"
        "out vec4 fragment_color;"
        ""
        "void main()"
        "{"
        "    fragment_color = vec4(front_color, 1.0);"
        "}";

    /**
     *@brief Constructor por defecto
     */
    Shader::Shader(ShaderType type, const std::string & vertex_source, const std::string & fragment_source)
    : m_type(type), m_vertex_source(vertex_source), m_fragment_source(fragment_source)
    {
        std::cout << "Loading custom shader..." << std::endl;
        std::cout << vertex_source << " | " << fragment_source << std::endl;
        std::string vertex_code, fragment_code;
        try
        {
            std::ifstream vertex_file(absolute_path + vertex_source);
            std::ifstream fragment_file(absolute_path + fragment_source);
            
            std::stringstream vertex_stream, fragment_stream;
            vertex_stream << vertex_file.rdbuf();
            fragment_stream << fragment_file.rdbuf();
            
            vertex_code = vertex_stream.str();
            fragment_code = fragment_stream.str();
        }
        catch (std::ifstream::failure& e)
        {
            std::cerr << "Error: No se pudieron leer los archivos de los shaders."<< std::endl;
            return;
        }
        
        glEnable     (GL_CULL_FACE);
        glDisable    (GL_DEPTH_TEST);
        glClearColor (.2f, .2f, .2f, 1.f);

        program_id = compile_shaders (vertex_code.c_str(), fragment_code.c_str());
    }

    Shader::Shader()
    {
        std::cout << "Loading default shader..." << std::endl;
        glEnable     (GL_CULL_FACE);
        glDisable    (GL_DEPTH_TEST);
        glClearColor (.2f, .2f, .2f, 1.f);

        program_id = compile_shaders (default_vertex_shader_code.c_str(), default_fragment_shader_code.c_str());
    }
    
    /**
     *@brief Compilador de los shaders construidos
     */
    GLuint Shader::compile_shaders(const char * vertex_shader_code, const char * fragment_shader_code)
    {
        GLint succeeded = GL_FALSE;
        
        // Shader creation
        GLuint vertex_shader_id     = glCreateShader(GL_VERTEX_SHADER);
        GLuint fragment_shader_id   = glCreateShader(GL_FRAGMENT_SHADER);
        
        // Load code of shaders
        const char* vertex_shaders_code[]   = {         vertex_shader_code };
        const char* fragment_shaders_code[] = {         fragment_shader_code };
        const GLint vertex_shaders_size[]   = { (GLint) std::strlen(vertex_shader_code) };
        const GLint fragment_shaders_size[] = { (GLint) std::strlen(fragment_shader_code) };
        
        glShaderSource(vertex_shader_id, 1, vertex_shaders_code, vertex_shaders_size);
        glShaderSource(fragment_shader_id, 1, fragment_shaders_code, fragment_shaders_size);
        
        // Shaders compile
        glCompileShader(vertex_shader_id);
        glCompileShader(fragment_shader_id);
        
        // Check compilation
        glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &succeeded);
        if (!succeeded)
        {
            show_compilation_error(vertex_shader_id);
        }
        glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &succeeded);
        if (!succeeded)
        {
            show_compilation_error(fragment_shader_id);
        }
        
        // Creation of shader program object
        GLuint program_id = glCreateProgram();
        
        // Load compiled shaders into program
        glAttachShader(program_id, vertex_shader_id);
        glAttachShader(program_id, fragment_shader_id);
        
        // Link shaders
        glLinkProgram(program_id);
        
        // Check if linkage was succesfull
        glGetProgramiv(program_id, GL_LINK_STATUS, &succeeded);
        if (!succeeded)
        {
            show_linkage_error(program_id);
        }
        
        // When linked, free the compiled shaders
        glDeleteShader(vertex_shader_id);
        glDeleteShader(fragment_shader_id);
        
        std::cout << "Shader program created" << std::endl;
        
        model_view_matrix_id = glGetUniformLocation(program_id, "model_view_matrix");
        projection_matrix_id = glGetUniformLocation(program_id, "projection_matrix");
        
        return (program_id);
    }

    void Shader::set_texture(const std::shared_ptr<Texture> & texture)
    {
        textures.push_back(texture);
    }

    void Shader::use() const
    {
        glUseProgram(program_id);
        
        // std::cout << "Textures size: " << textures.size() << std::endl;
        
        for (GLint i = 0; i < textures.size(); ++i)
        {
            textures[i]->bind();
            std::string uniform_name = "texture" + std::to_string(i);
            glUniform1i(glGetUniformLocation(program_id, uniform_name.c_str()), i);
        }
    }

    void Shader::set_texture_scale(float scale)
    {
        glUseProgram(program_id);
        GLint scale_location = glGetUniformLocation(program_id, "texture_scale");
        glUniform1f(scale_location, scale);
    }
    
    /**
     *@brief Mostrar errores de compilacion
     *
     *@param shader_id El id del shader que ha tenido el error de compilación
     */
    void Shader::show_compilation_error (GLuint shader_id)
    {
        std::string info_log;
        GLint  info_log_length;

        glGetShaderiv (shader_id, GL_INFO_LOG_LENGTH, &info_log_length);

        info_log.resize (info_log_length);

        glGetShaderInfoLog (shader_id, info_log_length, NULL, &info_log.front ());

        std::cerr << info_log.c_str () << std::endl;
    }

    /**
     *@brief Mostrar errores de enlace
     *
     *@param program_id El id del shader program que ha fallado en su enlace
     */
    void Shader::show_linkage_error (GLuint program_id)
    {
        std::string info_log;
        GLint  info_log_length;

        glGetProgramiv (program_id, GL_INFO_LOG_LENGTH, &info_log_length);

        info_log.resize (info_log_length);

        glGetProgramInfoLog (program_id, info_log_length, NULL, &info_log.front ());

        std::cerr << info_log.c_str () << std::endl;
    }
}
