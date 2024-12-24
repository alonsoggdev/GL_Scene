//
//  Camera.hpp
//  GL_Scene
//
//  Created by Alonso García on 23/12/24.
//

#pragma once

#include "glm.hpp"
#include <gtc/matrix_transform.hpp>
#include <gtc/constants.hpp>

enum class CameraMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera
{
public:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 world_up;
    
    float yaw;
    float pitch;
    
    float movement_speed;
    float mouse_sensitivity;
    float zoom;
    
    Camera(glm::vec3 start_position, glm::vec3 up_direction, float start_yaw, float start_pitch);
    
    glm::mat4 get_view_matrix() const;
    void process_keyboard(CameraMovement direction, float delta_time);
    void process_mouse_movement(float x_offset, float y_offset, bool constraint_pitch = true);
private:
    void update_camera_vectors();
};
