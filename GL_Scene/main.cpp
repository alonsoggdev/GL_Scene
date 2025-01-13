//
//  main.cpp
//  GL_Geometry
//
//  Created by Alonso García on 9/12/24.
//
/*
 */

#include <glad.h>
#include <SDL.h>
#include <iostream>
#include <fstream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include "Window.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include "EventHandler.hpp"

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
        
        SDL_SetRelativeMouseMode(SDL_TRUE);
        
        Scene scene(viewport_width, viewport_height);
        Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f);
        EventHandler event_handler(camera);
        
        
        // Main loop
        bool running = true;
        float last_frame = 0.0f;
        
        while (running)
        {
            float current_frame = SDL_GetTicks() / 1000.0f;
            float delta_time = current_frame - last_frame;
            last_frame = current_frame;
            
            event_handler.handle_events(running, delta_time);
            
            glm::mat4 view = camera.get_view_matrix();
            scene.set_view_matrix(view);
            
            glm::mat4 projection = glm::perspective
            (
                glm::radians(camera.zoom),
                float(viewport_width) / float(viewport_height),
                0.1f,
                100.0f
            );
            scene.set_projection_matrix(projection);
            
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
