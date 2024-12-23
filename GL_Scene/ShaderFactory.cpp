//
//  ShaderFactory.cpp
//  GL_Scene
//
//  Created by Alonso García on 20/12/24.
//

#include "ShaderFactory.hpp"

std::unique_ptr < udit::Shader > ShaderFactory::make_shader(udit::ShaderType type, const std::string & vertex_shader, const std::string & fragment_shader)
{
    switch (type)
    {
        case udit::ShaderType::SKYBOX:
        case udit::ShaderType::GEOMETRY:
            return std::make_unique<udit::Shader>(type, vertex_shader, fragment_shader);
        default:
            return std::make_unique<udit::Shader>();
    }
}

