//
//  Skybox.hpp
//  GL_Scene
//
//  Created by Alonso García on 21/12/24.
//
#pragma once

#include "Cube.hpp"

#include <vector>
#include <string>

namespace udit
{
    class Skybox : public Cube
    {
    private:
        unsigned int cubemapTexture;
        //std::string filepath  = "/../../../../../resources/skybox/";
        std::string filepath = "/Users/alonsoggdev/UDIT/Asignaturas/Programacion_Grafica/GL_Scene/resources/skybox/";
    public:
        Skybox();
        Skybox(float size, const std::vector<std::string>& faces);
        
        unsigned int getCubemapTexture() const { return cubemapTexture; }
    private:
        void loadCubemap(const std::vector<std::string>& faces);
    };
}
