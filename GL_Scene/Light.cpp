//
//  Light.cpp
//  GL_Scene
//
//  Created by Alonso García on 11/1/25.
//

#include "Light.hpp"

Light::Light(const glm::vec4 & pos, const glm::vec3 & col)
: position(pos), color(col) {}

void Light::send_to_shader(GLuint shaderProgram) const
{
    glUniform4fv(glGetUniformLocation(shaderProgram, "light.position"), 1, glm::value_ptr(position));
    
    glUniform3fv(glGetUniformLocation(shaderProgram, "light.color"), 1, glm::value_ptr(color));
}

