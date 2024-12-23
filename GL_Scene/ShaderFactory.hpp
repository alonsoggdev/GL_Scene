//
//  ShaderFactory.hpp
//  GL_Scene
//
//  Created by Alonso García on 20/12/24.
//

#include "Shader.hpp"

class ShaderFactory
{
private:
    
public:
    static std::unique_ptr < udit::Shader > make_shader(udit::ShaderType type = udit::ShaderType::DEFAULT, const std::string & vertex_shader = "", const std::string & fragment_shader = "");
};
