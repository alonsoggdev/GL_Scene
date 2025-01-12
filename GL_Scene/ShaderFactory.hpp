//
//  ShaderFactory.hpp
//  GL_Scene
//
//  Created by Alonso García on 20/12/24.
//

#include "Shader.hpp"

class ShaderFactory
{
public:
    static std::shared_ptr < udit::Shader > make_shader(
        udit::ShaderType type = udit::ShaderType::DEFAULT,
        const std::string & vertex_shader = "",
        const std::string & fragment_shader = "",
        const std::vector<std::string> & texture_paths = {}
    );
};
