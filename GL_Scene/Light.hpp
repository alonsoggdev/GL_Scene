//
//  Light.hpp
//  GL_Scene
//
//  Created by Alonso García on 11/1/25.
//

#include "glm.hpp"
#include "gtc/type_ptr.hpp"
#include "glad.h"

#include <iostream>
class Light {
private:
    glm::vec3 position;
    glm::vec3 color;
public:
    Light(const glm::vec4 & pos, const glm::vec3 & col);
    
    void send_to_shader(GLuint shaderProgram) const;
};
