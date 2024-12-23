//
//  Skybox.cpp
//  GL_Geometry
//
//  Created by Alonso García on 21/12/24.
//

#include "Skybox.hpp"
#include "SOIL2.h"  // Librería SOIL2 para cargar texturas
#include <iostream>
#include <unistd.h>

using udit::Skybox;

namespace udit
{
    Skybox::Skybox() : Cube(true)
    {
        cubemapTexture = 0;
    }

    Skybox::Skybox(float size, const std::vector<std::string>& faces) : Cube(size, true)
    {
        loadCubemap(faces);
    }

    void Skybox::loadCubemap(const std::vector<std::string>& faces)
    {
        glGenTextures(1, &cubemapTexture);
        glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
        
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != nullptr)
        {
            std::cout << "Directorio actual de trabajo: " << cwd << std::endl;
        }
        else
        {
            perror("getcwd error");
        }

        for (unsigned int i = 0; i < faces.size(); i++)
        {
            int width, height, channels;

            std::string filename = filepath + faces[i];
                        
            // std::cout << "Searching image in path: " << filename << std::endl;

            unsigned char* image = SOIL_load_image(filename.c_str(), &width, &height, &channels, SOIL_LOAD_RGB);

            if (image)
            {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
                             GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
                glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

                SOIL_free_image_data(image);
            }
            else
            {
                std::cerr << "Error al cargar la textura del cubemap: " << faces[i] << ": " << SOIL_last_result() << std::endl;
            }
        }
    }
    
}
