//
//  main.cpp
//  GL_Geometry
//
//  Created by Alonso García on 9/12/24.
//
/*
    Dudas:
        Cuando me dijo lo de hacer la clase Shader en una factoria, era para hacer una clase ShaderFactory que se encargase de construir diferentes sahders?
 */

#include <glad.h>
#include <SDL.h>
#include <iostream>
#include <fstream>
#include "Window.hpp"
#include "Scene.hpp"

using udit::Window;
using udit::Scene;

int main(int argc, char* argv[])
{
    std::cout << "Executing in " << argv[0] << std::endl;
    
    // Create window with Window class
    try
    {
        constexpr unsigned viewport_width = 1024;
        constexpr unsigned viewport_height = 720;

        Window window
        (
            "GL Scene",
            Window::Position::CENTERED,
            Window::Position::CENTERED,
            viewport_width,
            viewport_height,
            { 3,3 }
        );
        
        int major, minor;
        SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &major);
        SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minor);
        std::cout << "OpenGL Version: " << major << "." << minor << std::endl;


        // Initialize GLAD
        if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
        {
            std::cerr << "Error al inicializar GLAD" << std::endl;
            return -1;
        }
        
        Scene scene(viewport_width, viewport_height);
        
        // Main loop
        bool running = true;
        SDL_Event event;
        while (running)
        {
            // Event handler
            while (SDL_PollEvent(&event))
            {
                if (event.type == SDL_QUIT)
                {
                    running = false;
                }
            }
            
            scene.update();
            
            scene.render();
            
            window.swap_buffers();
        }

    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        SDL_Quit();
        return -1;
    }
    SDL_Quit();
    return 0;
}
