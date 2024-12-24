//
//  EventHandler.hpp
//  GL_Scene
//
//  Created by Alonso García on 23/12/24.
//

#pragma once

#include "SDL.h"
#include "glm.hpp"
#include "Camera.hpp"

class EventHandler
{
public:
    EventHandler(Camera& camera)
        : camera(camera), first_mouse(true), last_x(0.0f), last_y(0.0f) {}
    
    void handle_events(bool & running, float delta_time);
private:
    Camera & camera;
    bool first_mouse;
    float last_x;
    float last_y;
    
    void process_mouse_motion   (const SDL_Event & event);
    void process_keyboard       (const Uint8 * keystate, float delta_time);
};
