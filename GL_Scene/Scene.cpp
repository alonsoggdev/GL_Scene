//
//  Scene.cpp
//  GL_Geometry
//
//  Created by Alonso García on 9/12/24.
//

#include "Scene.hpp"
#include "Shader.hpp"
#include "Light.hpp"
#include "ShaderFactory.hpp"
#include "MeshFactory.hpp"

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
    Scene::Scene(unsigned width, unsigned height) :
    skybox(100.0f, skybox_faces), terrain(100.0f)
    {
        // std::cout << "Creating scene..." << std::endl;
        
        std::shared_ptr< Shader > default_shader_program = ShaderFactory::make_shader(udit::ShaderType::DEFAULT);
                
        std::shared_ptr < Shader > skybox_shader_program = ShaderFactory::make_shader(udit::ShaderType::SKYBOX, "Shader_Skybox_Vertex.glsl", "Shader_Skybox_Fragment.glsl");
        skybox.set_shader(std::move(skybox_shader_program));

        std::shared_ptr< Shader > terrain_shader_program = ShaderFactory::make_shader(udit::ShaderType::TERRAIN, "Shader_Terrain_Vertex.glsl", "Shader_Terrain_Fragment.glsl", {"height-map.png"});
        terrain.set_shader(std::move(terrain_shader_program));
        terrain.set_mesh_type(udit::MeshType::TERRAIN);
        
        bull = MeshFactory::make_mesh("bull.obj");
        bull->set_shader(std::move(default_shader_program));

        resize(width, height);
    }
    /**
     *@brief Actualiza ciertos valores dentro del bucle principal
     */
    void Scene::update()
    {
        angle += 0.01f;
    }
    
    /**
     *@brief Renderiza los elementos de la escena
     */
    void Scene::render ()
    {
        // std::cout << "Rendering scene..." << std::endl;
        
        glClear (GL_COLOR_BUFFER_BIT);
        
        //* Skybox rendering
        skybox.set_model_view_matrix(glm::mat4(1.0f));
        skybox.rotate(glm::vec3(1.0f, 0.0f, 0.0f), 180.0f);
        skybox.render(view_matrix);
                
        //* Terrain rendering
        terrain.set_model_view_matrix(glm::mat4(1.0f));
        terrain.translate(glm::vec3(0.0f, -10.0f, 0.0f));
        terrain.render(view_matrix);
        
        //* Bull rendering
        bull->set_model_view_matrix(glm::mat4(1.0f));
        bull->scale(glm::vec3(0.01f, 0.01f, 0.01f));
        bull->rotate(glm::vec3(1.0f, 0.0f, 0.0f), -90.0f);
        bull->translate(glm::vec3(0.0f, 0.0f, -5.0f));
        bull->render(view_matrix);
    }
    
    void Scene::resize (unsigned width, unsigned height)
    {
        std::vector < GLint > skybox_matrix_ids = skybox.get_shader_matrix_ids();
        std::vector < GLint > terrain_matrix_ids = terrain.get_shader_matrix_ids();
        std::vector < GLint > bull_matrix_ids = bull->get_shader_matrix_ids();

        glm::mat4 projection_matrix = glm::perspective (20.f, GLfloat(width) / height, 1.f, 5000.f);

        glUseProgram(skybox.get_shader_program_id());
        glUniformMatrix4fv(skybox_matrix_ids[1], 1, GL_FALSE, glm::value_ptr(projection_matrix));
        
        glUseProgram(terrain.get_shader_program_id());
        glUniformMatrix4fv(terrain_matrix_ids[1], 1, GL_FALSE, glm::value_ptr(projection_matrix));
        
        glUseProgram(bull->get_shader_program_id());
        glUniformMatrix4fv(bull_matrix_ids[1], 1, GL_FALSE, glm::value_ptr(projection_matrix));

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
}
