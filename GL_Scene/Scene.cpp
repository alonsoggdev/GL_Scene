//
//  Scene.cpp
//  GL_Geometry
//
//  Created by Alonso García on 9/12/24.
//

#include "Scene.hpp"

#include <iostream>

#include <glm.hpp>

using udit::Shader;

namespace udit
{
    /**
     *@brief Constructor
     *
     *Inicializa una escena
     *@param width Ancho de la escena
     *@param height Alto de la escena
     */
    Scene::Scene(unsigned width, unsigned height)
    {
        std::shared_ptr< PointLight > light = std::dynamic_pointer_cast< PointLight >(Light::make_light(LightType::POINT, glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(7.0f, 7.0f, 7.0f)));
        lights.push_back(light);
        std::cout << "Creating " << lights.size() << " lights." << std::endl;
        // std::cout << "Creating scene..." << std::endl;
        std::shared_ptr< Shader > default_shader_program = Shader::make_shader(udit::ShaderType::DEFAULT);
        /*
        
        // SKYBOX
        skybox = std::dynamic_pointer_cast<Skybox>(Mesh::make_mesh(udit::MeshType::SKYBOX));
        skybox->set_mesh_type(udit::MeshType::SKYBOX);
        std::shared_ptr < Shader > skybox_shader_program = Shader::make_shader(udit::ShaderType::SKYBOX,
                                                                               "Shader_Skybox_Vertex.glsl",
                                                                               "Shader_Skybox_Fragment.glsl",
                                                                               {""},
                                                                               {"Skybox"});
        skybox->set_shader(skybox_shader_program);
        
        // TERRAIN
        std::vector<std::string> textures = {"height-map.jpg"};
        terrain = std::dynamic_pointer_cast<Plane>(Mesh::make_mesh(udit::MeshType::TERRAIN));
        terrain->set_mesh_type(udit::MeshType::TERRAIN);
        std::shared_ptr< Shader > terrain_shader_program = Shader::make_shader(udit::ShaderType::TERRAIN, "Shader_Terrain_Vertex.glsl", "Shader_Terrain_Fragment.glsl", {"height-map.jpg"}, "Terrain");
        terrain->set_shader(terrain_shader_program);
        
        // PLANE
        floor = std::dynamic_pointer_cast<Plane>(Mesh::make_mesh(udit::MeshType::BASIC));
        floor->set_mesh_type(MeshType::BASIC);
        std::shared_ptr< Shader > floor_shader_program = Shader::make_shader(udit::ShaderType::SINGLE_TEXTURE, "Shader_SingleTexture_Vertex.glsl", "Shader_SingleTexture_Fragment.glsl", {"snow.jpg"}, "Floor");
        floor->set_shader(floor_shader_program);
         */

        //BULL
        bull = Mesh::make_mesh(udit::MeshType::MESH, "bull.obj");
        
        bull->set_shader(default_shader_program);
        
        glUseProgram(bull->get_shader_program_id());
        GLint material_color = glGetUniformLocation(bull->get_shader_program_id(), "material_color");
        if (material_color == -1)
        {
            std::cout << "Material color not found in shader" << std::endl;
        }
        glUniform3f(material_color, 1.0f, 1.0f, 0.0f);

        set_lights(bull->get_shader_program_id());
        glUseProgram(0);
        
        resize(width, height);
    }
    /**
     *@brief Actualiza ciertos valores dentro del bucle principal
     */
    void Scene::update()
    {
        angle += 0.5f;
    }
    
    /**
     *@brief Renderiza los elementos de la escena
     */
    void Scene::render ()
    {
        // std::cout << "Rendering scene..." << std::endl;
        
        glClear (GL_COLOR_BUFFER_BIT);

        /*
        //* Skybox rendering
        glm::mat4 skybox_view_matrix = glm::mat4(glm::mat3(view_matrix));
        skybox->set_model_view_matrix(glm::mat4(1.0f));
        skybox->render(skybox_view_matrix);
                
        //* Terrain rendering
        terrain->set_model_view_matrix(glm::mat4(1.0f));
        terrain->translate(glm::vec3(0.0f, -2.0f, -100.0f));
        terrain->rotate(glm::vec3(1.0f, 0.0f, 0.0f), 90.0f);
        terrain->render(view_matrix);
        
        //* Floor rendering
        floor->set_model_view_matrix(glm::mat4(1.0f));
        floor->translate(glm::vec3(0.0f, -2.0f, 0.0f));
        floor->rotate(glm::vec3(1.0f, 0.0f, 0.0f), 90.0f);
        floor->render(view_matrix);
         */

        //* Bull rendering
        bull->set_model_view_matrix(glm::mat4(1.0f));
        bull->translate(glm::vec3(0.0f, -2.0f, -5.0f));
        bull->rotate(glm::vec3(1.0f, 0.0f, 0.0f), -90.0f);
        bull->rotate(glm::vec3(0.0f, 0.0f, 1.0f), angle);
        bull->scale(glm::vec3(0.01f, 0.01f, 0.01f));
        bull->render(view_matrix);
    }
    
    void Scene::resize (unsigned width, unsigned height)
    {
        glm::mat4 projection_matrix = glm::perspective (20.f, GLfloat(width) / height, 1.f, 5000.f);
        /*
        skybox->resize(projection_matrix);
        terrain->resize(projection_matrix);
        floor->resize(projection_matrix);
         */
        bull->resize(projection_matrix);

        glViewport (0, 0, width, height);
    }

    void Scene::set_view_matrix(const glm::mat4& view)
    {
        view_matrix = view;
    }

    void Scene::set_projection_matrix(const glm::mat4& projection)
    {
        projection_matrix = projection;
    }

    void Scene::set_lights(GLuint shader_program_id)
    {
        glUseProgram (shader_program_id);
        for (size_t i = 0; i < lights.size(); ++i)
        {
            std::string light_index = "lights[" + std::to_string(i) + "]";
            std::string aux_var;
            aux_var = light_index +     ".color";
            GLint light_color_id     = glGetUniformLocation (shader_program_id, aux_var.c_str());
            
            aux_var = light_index +  ".position";
            GLint light_position_id  = glGetUniformLocation (shader_program_id, aux_var.c_str());
            
            aux_var = light_index +  ".constant";
            GLint light_constant_id  = glGetUniformLocation (shader_program_id, aux_var.c_str());
            
            aux_var = light_index +    ".linear";
            GLint light_linear_id    = glGetUniformLocation (shader_program_id, aux_var.c_str());
            
            aux_var = light_index + ".quadratic";
            GLint light_quadratic_id = glGetUniformLocation (shader_program_id, aux_var.c_str());
            
            glUniform3fv (light_color_id, 1, glm::value_ptr(lights[i]->color));
            
            if (auto dir_light = std::dynamic_pointer_cast<DirectionalLight>(lights[i]))
            {
                glUniform4f (light_position_id, dir_light->direction.x, dir_light->direction.y, dir_light->direction.z, 0.0f);
                glUniform1f (light_constant_id, 1.0f);
                glUniform1f (light_linear_id, 0.0f);
                glUniform1f (light_quadratic_id, 0.0f);
            }
            else
            if (auto point_light = std::dynamic_pointer_cast<PointLight>(lights[i]))
            {
                std::cout << "Configuring point light at position: " << point_light->position.x << ", " << point_light->position.y << ", " << point_light->position.z << "." << std::endl;
                glUniform4f(light_position_id, point_light->position.x, point_light->position.y, point_light->position.z, 1.0f);
                glUniform1f(light_constant_id, 1.0f);
                glUniform1f(light_linear_id, 0.09f);
                glUniform1f(light_quadratic_id, 0.032f);
            }
            else
            if (auto area_light = std::dynamic_pointer_cast<AreaLight>(lights[i]))
            {
                glUniform4f(light_position_id, area_light->position.x, area_light->position.y, area_light->position.z, 1.0f);
                glUniform1f(light_constant_id, 1.0f);
                glUniform1f(light_linear_id, 0.09f);
                glUniform1f(light_quadratic_id, 0.032f);
            }
        }
        
        GLint  ambient_intensity_id = glGetUniformLocation(shader_program_id, "ambient_intensity");
        GLint  diffuse_intensity_id = glGetUniformLocation(shader_program_id,  "diffuse_intensity");
        GLint specular_intensity_id = glGetUniformLocation(shader_program_id, "specular_intensity");
        
        glUniform1f ( ambient_intensity_id, 0.2f);
        glUniform1f ( diffuse_intensity_id, 0.8f);
        glUniform1f (specular_intensity_id, 1.0f);
        
        
        glUseProgram (0);
    }
}
