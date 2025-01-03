//
//  Scene.cpp
//  GL_Geometry
//
//  Created by Alonso García on 9/12/24.
//

#include "Scene.hpp"
#include "Shader.hpp"
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
        std::unique_ptr< Shader > default_shader_program = ShaderFactory::make_shader(udit::ShaderType::DEFAULT);
        
        std::unique_ptr < Shader > skybox_shader_program = ShaderFactory::make_shader(udit::ShaderType::SKYBOX, "Shader_Skybox_Vertex.glsl", "Shader_Skybox_Fragment.glsl");
        skybox.set_shader(std::move(skybox_shader_program));

        std::unique_ptr< Shader > terrain_shader_program = ShaderFactory::make_shader(udit::ShaderType::TERRAIN, "Shader_Terrain_Vertex.glsl", "Shader_Terrain_Fragment.glsl", {"height-map.png"});
        terrain.set_shader(std::move(terrain_shader_program));
        terrain.set_mesh_type(udit::MeshType::TERRAIN);
        
        bull = MeshFactory::make_mesh("bull.obj");
        bull->set_shader(std::move(default_shader_program));
        bull->set_mesh_type(udit::MeshType::MESH);

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
        
        glm::mat4 model_view_matrix(1);
        
        //* Skybox rendering
        glUseProgram(skybox.get_shader_program_id());
        glm::mat4 skybox_matrix = glm::translate(model_view_matrix, glm::vec3(0.0f, -1.0f, 0.0f));
        skybox_matrix = glm::rotate(skybox_matrix, glm::radians(180.0f), glm::vec3(1.f, 0.f, 0.f));
        glm::mat4 skybox_model_view_matrix = view_matrix * skybox_matrix;
        glUniformMatrix4fv(skybox.get_shader_matrix_ids().first, 1, GL_FALSE, glm::value_ptr(skybox_model_view_matrix));
        skybox.render();
        
        //* Terrain rendering
        glUseProgram(terrain.get_shader_program_id());
        glm::mat4 terrain_matrix = glm::translate(model_view_matrix, glm::vec3(0.0f, -20.0f, 0.0f));
        //terrain_matrix = glm::rotate(terrain_matrix, glm::radians(90.0f), glm::vec3(1.0f, 0.f, 0.f));
        glm::mat4 terrain_model_view_matrix = view_matrix * terrain_matrix;
        glUniformMatrix4fv(terrain.get_shader_matrix_ids().first, 1, GL_FALSE, glm::value_ptr(terrain_model_view_matrix));
        terrain.render();
        
        glm::mat4 bull_matrix = glm::translate(model_view_matrix, glm::vec3(0.0f, 0.0f, 0.0f));
        // bull_matrix = glm::rotate(bull_matrix, glm::radians(0.0f), glm::vec3(0.f, 0.f, 0.f));
        glm::mat4 bull_model_view_matrix = view_matrix * bull_matrix;
        glUniformMatrix4fv(bull->get_shader_matrix_ids().first, 1, GL_FALSE, glm::value_ptr(bull_model_view_matrix));
        bull->render();
        
    }
    
    void Scene::resize (unsigned width, unsigned height)
    {
        std::pair < GLint, GLint > skybox_matrix_ids = skybox.get_shader_matrix_ids();
        std::pair < GLint, GLint > terrain_matrix_ids = terrain.get_shader_matrix_ids();
        std::pair < GLint, GLint > bull_matrix_ids = bull->get_shader_matrix_ids();

        glm::mat4 projection_matrix = glm::perspective (20.f, GLfloat(width) / height, 1.f, 5000.f);

        glUseProgram(skybox.get_shader_program_id());
        glUniformMatrix4fv(skybox_matrix_ids.second, 1, GL_FALSE, glm::value_ptr(projection_matrix));
        
        glUseProgram(terrain.get_shader_program_id());
        glUniformMatrix4fv(terrain_matrix_ids.second, 1, GL_FALSE, glm::value_ptr(projection_matrix));
        
        glUseProgram(bull->get_shader_program_id());
        glUniformMatrix4fv(bull_matrix_ids.second, 1, GL_FALSE, glm::value_ptr(projection_matrix));

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
