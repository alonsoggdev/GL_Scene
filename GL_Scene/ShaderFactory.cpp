//
//  ShaderFactory.cpp
//  GL_Scene
//
//  Created by Alonso García on 20/12/24.
//

#include "ShaderFactory.hpp"

using udit::Texture;

std::unique_ptr < udit::Shader > ShaderFactory::make_shader(
    udit::ShaderType type,
    const std::string & vertex_shader,
    const std::string & fragment_shader,
    const std::vector<std::string> & texture_paths
)
{
    std::string absolute_path = "/Users/alonsoggdev/UDIT/Asignaturas/Programacion_Grafica/GL_Scene/resources/";

    auto shader = std::make_unique<udit::Shader>(type, vertex_shader, fragment_shader);
    switch (type)
    {
        case udit::ShaderType::SKYBOX:
        case udit::ShaderType::GEOMETRY:
        case udit::ShaderType::SINGLE_TEXTURE:
        case udit::ShaderType::TERRAIN:
            break;
        default:
            shader = nullptr;
            return std::make_unique<udit::Shader>();
    }
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
    for (const auto & path : texture_paths)
    {
        std::string complete_path = absolute_path + path;
        auto texture = std::make_shared<Texture>(complete_path, texture_unit);
        
        if (texture->is_loaded())
        {
            shader->set_texture(texture);
            shader->set_texture_scale(5.0f);
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
    
    return shader;
}

