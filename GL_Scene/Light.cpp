//
//  NewLight.cpp
//  GL_Scene
//
//  Created by Alonso García on 13/1/25.
//

#include "Light.hpp"

using namespace udit;

Light::Light(const glm::vec3& pos, const glm::vec3& col, float ambient, float diffuse, float specular)
    : position(pos), color(col), ambientIntensity(ambient), diffuseIntensity(diffuse), specularIntensity(specular)
{
    std::cout << "Creating light in position -> " << position.x << ", " << position.y << ", " << position.z << std::endl;
}


void Light::send_to_shader(GLuint shaderProgram, const std::string& uniformName) const
{
    // std::cout << "Sending light to shader " << shaderProgram << std::endl;
    glUniform3fv(glGetUniformLocation(shaderProgram, (uniformName + ".position").c_str()), 1, &position[0]);
    glUniform3fv(glGetUniformLocation(shaderProgram, (uniformName + ".color").c_str()), 1, &color[0]);
    glUniform1f(glGetUniformLocation(shaderProgram, (uniformName + ".ambient_intensity").c_str()), ambientIntensity);
    glUniform1f(glGetUniformLocation(shaderProgram, (uniformName + ".diffuse_intensity").c_str()), diffuseIntensity);
    glUniform1f(glGetUniformLocation(shaderProgram, (uniformName + ".specular_intensity").c_str()), specularIntensity);
}
