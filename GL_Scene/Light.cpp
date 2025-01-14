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


void Light::send_to_shader(GLuint program_id, const std::string& uniformName) const
{
    GLint material_color = glGetUniformLocation (program_id, "material_color");

    glUniform3f (material_color, 1.0f, 0.0f, 0.0f);
    
    GLint light_position    = glGetUniformLocation (program_id, "light.position");
    GLint light_color       = glGetUniformLocation (program_id, "light.color"   );
    GLint ambient_intensity = glGetUniformLocation (program_id, "ambient_intensity");
    GLint diffuse_intensity = glGetUniformLocation (program_id, "diffuse_intensity");

    glUniform4f (light_position,   10.0f, 10.f, 10.f, 1.f);
    glUniform3f (light_color,       1.0f,  1.f,  1.f);
    glUniform1f (ambient_intensity, 0.2f);
    glUniform1f (diffuse_intensity, 0.8f);


}
