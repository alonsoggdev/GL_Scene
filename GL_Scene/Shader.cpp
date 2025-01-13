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
        "uniform mat4 normal_matrix;"
        ""
        "layout (location = 0) in vec3 vertex_coordinates;"
        "layout (location = 1) in vec3 vertex_normal;"
        "layout (location = 2) in vec2 vertex_texture_uv;"
        ""
        "out vec3 normal;"
        "out vec3 fragment_position;"
        "out vec2 texture_uv;"
        ""
        "void main()"
        "{"
        "   vec4 view_space_pos = model_view_matrix * vec4(vertex_coordinates, 1.0);"
        "   fragment_position = vec3(view_space_pos);"
        "   normal = normalize(mat3(normal_matrix) * vertex_normal);"
        "   texture_uv = vertex_texture_uv;"
        "   gl_Position = projection_matrix * view_space_pos;"
        "}";

    const std::string Shader::default_fragment_shader_code =
        "#version 330\n"
        ""
        "struct Light"
        "{"
        "   vec4 position;"
        "   vec3 color;"
        "   float constant;"
        "   float linear;"
        "   float quadratic;"
        "};"
        ""
        "uniform Light lights[3];"
        "uniform float ambient_intensity;"
        "uniform float diffuse_intensity;"
        "uniform float specular_intensity;"
        "uniform float shininess;"
        ""
        "uniform vec3 view_pos;"
        "uniform vec3 material_color;"
        ""
        "uniform sampler2D texture0;"
        ""
        "in  vec3            normal;"
        "in  vec3 fragment_position;"
        "in  vec2 texture_uv;"
        ""
        "out vec4    fragment_color;"
        ""
        "void main()"
        "{"
        "   vec3 result    = vec3(0.0);"
        "   vec3 light_dir = vec3(0.0);"
        "   vec3 norm      = normalize(normal);"
        "   vec3 view_dir  = normalize(view_pos - fragment_position);"
        ""
        "   for (int i = 0; i < 3 ; ++i)\n "
        "   {\n"
        "       vec3 light_dir    = normalize(vec3(lights[i].position) - fragment_position);"
        "       float distance    = length(vec3(lights[i].position) - fragment_position);"
        "       float attenuation = 1.0 / (lights[i].constant + lights[i].linear * distance + lights[i].quadratic * (distance * distance));"
        "       vec3 ambient      = ambient_intensity * lights[i].color;"
        "       float diff        = max(dot(norm, light_dir), 0.0);"
        "       vec3 diffuse      = diffuse_intensity * diff * lights[i].color;"
        "       vec3 halfway_dir  = normalize(light_dir + view_dir);"
        "       float spec        = pow(max(dot(norm, halfway_dir), 0.0), shininess);"
        "       vec3 specular     = specular_intensity * spec * lights[i].color;"
        ""
        "       ambient   *= attenuation;"
        "       diffuse   *= attenuation;"
        "       specular  *= attenuation;"
        "       result    += (ambient + diffuse + specular) * material_color;"
        "   }\n"
        "   fragment_color = vec4(result, 1.0) * vec4(texture (texture0, texture_uv.st).rgb, 1.0);"
        "}";

    Shader::Shader(ShaderType type, const std::string & vertex_source, const std::string & fragment_source, const std::string & name)
    : m_type(type), m_vertex_source(vertex_source), m_fragment_source(fragment_source), m_name(name)
    {
        std::cout << "Loading custom shader... " << std::endl;
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

    Shader::~Shader(){}

    std::shared_ptr < Shader > Shader::make_shader(
        udit::ShaderType type,
        const std::string & vertex_shader,
        const std::string & fragment_shader,
        const std::vector<std::string> & texture_paths,
        const std::string & name
    )
    {
        std::string absolute_path = "/Users/alonsoggdev/UDIT/Asignaturas/Programacion_Grafica/GL_Scene/resources/";

        switch (type)
        {
            case udit::ShaderType::SKYBOX:
            case udit::ShaderType::GEOMETRY:
            case udit::ShaderType::SINGLE_TEXTURE:
            case udit::ShaderType::TERRAIN:
                break;
            default:
                return std::make_shared<udit::Shader>();
        }
        auto shader = std::make_shared<udit::Shader>(type, vertex_shader, fragment_shader, name);
        
        GLenum texture_unit = GL_TEXTURE0;
        if (type == udit::ShaderType::TERRAIN)
        {
            std::cout << "TERRAIN SHADER" << std::endl;
            glUniform1d(glGetUniformLocation(shader->get_program_id(), "max_height"), 5.0f);
            std::string complete_path = absolute_path + texture_paths[0];
            auto texture = std::make_shared<Texture>(complete_path, texture_unit, udit::Texture_Type::HEIGHT);
            
            if (texture->is_loaded())
            {
                shader->set_texture(texture);
            }
            return shader;
        }
        std::cout << "Loading " << texture_paths.size() << " textures." << std::endl;
        for (const auto & path : texture_paths)
        {
            if (path == "") break;
            std::string complete_path = absolute_path + path;
            // std::cout << path << std::endl;
            auto texture = std::make_shared<Texture>(complete_path, texture_unit);
            
            if (texture->is_loaded())
            {
                shader->set_texture(texture);
                shader->set_texture_scale(1.0f);
                ++texture_unit;
            }
            else
            {
                std::cerr << "No se pudo cargar la textura desde " << complete_path << std::endl;
            }
            
            GLint max_texture_units;
            glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, &max_texture_units);
            if (texture_unit - GL_TEXTURE0 >= max_texture_units)
            {
                std::cerr << "Advertencia: Se superó el número máximo de unidades de textura (" << max_texture_units << "). Textura " << path << " no fue asociada." << std::endl;
                break;
            }
        }
        switch (type)
        {
            case udit::ShaderType::SKYBOX:
                shader->set_name("Skybox");
            case udit::ShaderType::GEOMETRY:
                shader->set_name("Geometry");
            case udit::ShaderType::SINGLE_TEXTURE:
                shader->set_name("Texture");
            case udit::ShaderType::TERRAIN:
                shader->set_name("Terrain");
                break;
            case udit::ShaderType::DEFAULT:
                shader->set_name("Default");
                break;
            default:
                shader->set_name("None");
                break;
        }
        return shader;
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
        normal_matrix_id     = glGetUniformLocation(program_id, "normal_matrix");
        
        //  Configure material
        GLint material_color = glGetUniformLocation(program_id, "material_color");
        glUniform3f(material_color, 0.f, 1.f, 0.f);
        
        // Configure light
        GLint light_position    = glGetUniformLocation (program_id, "light.position");
        GLint light_color       = glGetUniformLocation (program_id, "light.color"   );
        GLint ambient_intensity = glGetUniformLocation (program_id, "ambient_intensity");
        GLint diffuse_intensity = glGetUniformLocation (program_id, "diffuse_intensity");

        glUniform4f (light_position,   10.0f, 10.f, 10.f, 1.f);
        glUniform3f (light_color,       1.0f,  1.f,  1.f);
        glUniform1f (ambient_intensity, 10.f);
        glUniform1f (diffuse_intensity, 100.f);

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
        
        if (textures.size() > 0)
        {
            for (GLint i = 0; i < textures.size(); ++i)
            {
                textures[i]->bind();
                std::string uniform_name = "texture" + std::to_string(i);
                glUniform1i(glGetUniformLocation(program_id, uniform_name.c_str()), i);
            }
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
