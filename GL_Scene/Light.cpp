//
//  NewLight.cpp
//  GL_Scene
//
//  Created by Alonso García on 13/1/25.
//

#include "Light.hpp"

using namespace udit;


std::shared_ptr<Light> Light::make_light(LightType type, const glm::vec3& color, const glm::vec3& vec1, const glm::vec3& vec2)
{
    switch (type)
    {
    case LightType::DIRECTIONAL:
        return std::make_shared<DirectionalLight>(color, vec1);
    case LightType::POINT:
        return std::make_shared<PointLight>(color, vec1);
    case LightType::AREA:
        return std::make_shared<AreaLight>(color, vec1, vec2);
    default:
        return nullptr;
    }

}
