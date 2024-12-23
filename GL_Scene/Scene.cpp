//
//  Scene.cpp
//  GL_Geometry
//
//  Created by Alonso García on 9/12/24.
//

#include "Scene.hpp"
#include "Shader.hpp"
#include "ShaderFactory.hpp"

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
    skybox(5.0f, skybox_faces)
    {
        // std::cout << "Creating scene..." << std::endl;
        std::unique_ptr < Shader >skybox_shader_program = ShaderFactory::make_shader(udit::ShaderType::SKYBOX, "Shader_Skybox_Vertex.glsl", "Shader_Skybox_Fragment.glsl");
        
        skybox.set_shader(std::move(skybox_shader_program));
                
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
        
        std::pair < GLint, GLint > skybox_matrix_ids = skybox.get_shader_matrix_ids();
        
        model_view_matrix = glm::translate(model_view_matrix, glm::vec3(0.0f, -1.0f, 0.0f));
                        
        model_view_matrix = glm::rotate(model_view_matrix, glm::radians(180.0f), glm::vec3(1.f, 0.f, 0.f));

        glUniformMatrix4fv (skybox_matrix_ids.first, 1, GL_FALSE, glm::value_ptr(model_view_matrix));

        skybox.render();
         
    }
    
    void Scene::resize (unsigned width, unsigned height)
    {
        std::pair < GLint, GLint > skybox_matrix_ids = skybox.get_shader_matrix_ids();

        glm::mat4 projection_matrix = glm::perspective (20.f, GLfloat(width) / height, 1.f, 5000.f);

        glUniformMatrix4fv (skybox_matrix_ids.second, 1, GL_FALSE, glm::value_ptr(projection_matrix));

        glViewport (0, 0, width, height);
    }
}