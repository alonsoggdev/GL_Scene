//
//  Scene.hpp
//  GL_Geometry
//
//  Created by Alonso García on 9/12/24.
//

#pragma once

#include <string>
#include "Shader.hpp"

#include "Skybox.hpp"
#include "Cube.hpp"

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
                
        Skybox skybox;
        // Cube cube;
        
    public:
        Scene(unsigned width, unsigned height);

        void update();
        void render();
        void resize(unsigned width, unsigned height);
    };
}
