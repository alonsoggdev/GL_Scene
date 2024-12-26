//
//  EventHandler.cpp
//  GL_Scene
//
//  Created by Alonso García on 23/12/24.
//

#include "EventHandler.hpp"
#include <iostream>

void EventHandler::handle_events(bool& running, float delta_time)
{
    SDL_Event event;
    const Uint8* keystate = SDL_GetKeyboardState(NULL);

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            running = false;
        }
        else if (event.type == SDL_MOUSEMOTION)
        {
            process_mouse_motion(event);
        }
    }
    process_keyboard(keystate, delta_time);
}

void EventHandler::process_mouse_motion(const SDL_Event& event)
{
    float x_pos = static_cast<float>(event.motion.xrel);
    float y_pos = static_cast<float>(event.motion.yrel);
    
    y_pos = - y_pos; // Invertir el eje y
    
    // std::cout << x_pos << " " << y_pos << std::endl;

    camera.process_mouse_movement(x_pos, y_pos);
}

void EventHandler::process_keyboard(const Uint8* keystate, float delta_time)
{
    if (keystate[SDL_SCANCODE_W])
    {
        camera.process_keyboard(CameraMovement::FORWARD, delta_time);
    }
    if (keystate[SDL_SCANCODE_S])
    {
        camera.process_keyboard(CameraMovement::BACKWARD, delta_time);
    }
    if (keystate[SDL_SCANCODE_A])
    {
        camera.process_keyboard(CameraMovement::LEFT, delta_time);
    }
    if (keystate[SDL_SCANCODE_D])
    {
        camera.process_keyboard(CameraMovement::RIGHT, delta_time);
    }
}
