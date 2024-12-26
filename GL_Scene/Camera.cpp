//
//  Camera.cpp
//  GL_Scene
//
//  Created by Alonso García on 23/12/24.
//

#include "Camera.hpp"

#include <iostream>

Camera::Camera(glm::vec3 start_position, glm::vec3 up_direction, float start_yaw, float start_pitch)
      : position(start_position),
        world_up(up_direction),
        yaw(start_yaw),
        pitch(start_pitch),
        front(glm::vec3(0.0f, 0.0f, -1.0f)),
        movement_speed(2.5f),
        mouse_sensitivity(0.1f),
        zoom(45.0f)
{
    update_camera_vectors();
}

glm::mat4 Camera::get_view_matrix() const
{
    return glm::lookAt(position, position + front, up);
}

void Camera::process_keyboard(CameraMovement direction, float delta_time)
{
    float velocity = movement_speed * delta_time;
    
    if (direction == CameraMovement::FORWARD)
    {
        position += front * velocity;
    }
    
    if (direction == CameraMovement::BACKWARD)
    {
        position -= front * velocity;
    }
    
    if (direction == CameraMovement::LEFT)
    {
        position -= right * velocity;
    }
    
    if (direction == CameraMovement::RIGHT)
    {
        position += right * velocity;
    }
    
    // position.y = 0.0f;
}

void Camera::process_mouse_movement(float x_offset, float y_offset, bool constraint_pitch)
{
    x_offset *= mouse_sensitivity;
    y_offset *= mouse_sensitivity;
    
    yaw += x_offset;
    pitch += y_offset;
    
    // std::cout << yaw << std::endl;
    // std::cout << pitch << std::endl;
    
    if (constraint_pitch)
    {
        if (pitch > 89.0f)
        {
            pitch = 89.0f;
        }
        if (pitch < -89.0f)
        {
            pitch = -89.0f;
        }
    }
    
    update_camera_vectors();
}

void Camera::update_camera_vectors()
{
    glm::vec3 new_front;
    new_front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    new_front.y = sin(glm::radians(pitch));
    new_front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(new_front);

    right = glm::normalize(glm::cross(front, world_up));
    up = glm::normalize(glm::cross(right, front));

}
