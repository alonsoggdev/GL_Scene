//
//  NewLight.hpp
//  GL_Scene
//
//  Created by Alonso García on 13/1/25.
//

#pragma once

#include "glm.hpp"
#include <iostream>

#include "Cube.hpp"

namespace udit
{
    enum class LightType
    {
        DIRECTIONAL,
        POINT,
        AREA
    };

    class Light
    {
    public:
        glm::vec3 color;
        Light (const glm:: vec3 & color) : color(color) {}
        virtual ~Light() = default;
                
        static std::shared_ptr<Light> make_light(LightType type, const glm::vec3& color, const glm::vec3& vec1 = glm::vec3(0.0f), const glm::vec3& vec2 = glm::vec3(0.0f));
    };

    class DirectionalLight : public Light
    {
    public:
        glm::vec3 direction;
        DirectionalLight(const glm::vec3 & color, const glm::vec3 direction) : Light (color), direction (direction) {}
    };

    class PointLight : public Light
    {
    public:
        glm::vec3 position;
        PointLight(const glm::vec3 & color, const glm::vec3 & position) : Light (color), position (position) {}
    };

    class AreaLight : public Light
    {
    public:
        glm::vec3 position;
        glm::vec3 size;
        AreaLight (const glm::vec3 & color, const glm::vec3 & position, const glm::vec3 & size) :
        Light (color), position (position), size (size) {}
        
    };
}

