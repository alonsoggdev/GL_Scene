//
//  NewLight.hpp
//  GL_Scene
//
//  Created by Alonso García on 13/1/25.
//

#pragma once

#include "glm.hpp"
#include <iostream>

#include "Cube.hpp"

namespace udit
{
    class Light {
    private:
        glm::vec3 position;
        glm::vec3 color;
        float ambientIntensity;
        float diffuseIntensity;
        float specularIntensity;
    public:
        Light(const glm::vec3& pos, const glm::vec3& col, float ambient, float diffuse, float specular);

        void send_to_shader(GLuint program_id, const std::string& uniformName) const;
    };
}

