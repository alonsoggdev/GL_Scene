//
//  Scene.hpp
//  GL_Geometry
//
//  Created by Alonso García on 9/12/24.
//

#pragma once

#include <string>
#include "Shader.hpp"
#include "Light.hpp"
#include "Skybox.hpp"
#include "Plane.hpp"


namespace udit
{
    class Scene
    {
    private:
        std::vector<std::string> skybox_faces =
        {
               "skybox_east.jpg", "skybox_west.jpg", "skybox_up.jpg",
               "skybox_down.jpg", "skybox_north.jpg", "skybox_south.jpg"
        };
        
        float angle = 0.0f;
                
        std::shared_ptr<Skybox> skybox;
        std::shared_ptr<Plane> terrain;
        std::shared_ptr<Plane> floor;
        std::shared_ptr<Mesh> bull;
        Light light;
        
        unsigned width, height;
                
        glm::mat4 view_matrix;
        glm::mat4 projection_matrix;
        
    public:
        Scene(unsigned width, unsigned height);

        void update();
        void render();
        void resize(unsigned width, unsigned height);
        
        void set_view_matrix(const glm::mat4& view);
        void set_projection_matrix(const glm::mat4& projection);
        void set_lights(GLuint shader_program_id);
    };
}
