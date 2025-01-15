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
    Scene::Scene(unsigned width, unsigned height) : width(width), height(height)
    {
        // std::cout << "Creating scene..." << std::endl;

        std::shared_ptr< Shader > default_shader_program = Shader::make_shader(udit::ShaderType::DEFAULT);
        light = Light::make_light(glm::vec3(4.0f, 2.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), 0.2f, 0.8f);

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

        // BULL
        bull = Mesh::make_mesh(udit::MeshType::MESH, "bull.obj");
        bull->set_shader(default_shader_program);
        light->send_to_shader(bull->get_shader_program_id());
        
        // STATUE
        statue = Mesh::make_mesh(udit::MeshType::MESH, "buda.obj");
        statue->set_shader(default_shader_program);
        light->send_to_shader(statue->get_shader_program_id());
        
        resize(width, height);
    }
    /**
     *@brief Actualiza ciertos valores dentro del bucle principal
     */
    void Scene::update()
    {
       // angle += 0.5f;
    }
    
    /**
     *@brief Renderiza los elementos de la escena
     */
    void Scene::render ()
    {
        // std::cout << "Rendering scene..." << std::endl;
        
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
        
        //* Bull rendering
        bull->set_model_view_matrix(glm::mat4(1.0f));
        bull->translate(glm::vec3(0.0f, -2.0f, -5.0f));
        bull->rotate(glm::vec3(1.0f, 0.0f, 0.0f), -90.0f);
        bull->rotate(glm::vec3(0.0f, 0.0f, 1.0f), angle);
        bull->scale(glm::vec3(0.01f, 0.01f, 0.01f));
        bull->render(view_matrix);
        
        //* Statue rendering
        statue->set_model_view_matrix(glm::mat4(1.0f));
        //statue->translate(glm::vec3(0.0f, 0.0f, 0.0f));
        statue->scale(glm::vec3(30.0f, 30.0f, 30.0f));
        statue->orbit(glm::vec3(0.0f, 0.0f, 0.0f), 0.5f, 0.5f);
        statue->render(view_matrix);
    }
    
    void Scene::resize (unsigned width, unsigned height)
    {
        glm::mat4 projection_matrix = glm::perspective (20.f, GLfloat(width) / height, 1.f, 5000.f);

        skybox->resize(projection_matrix);
        terrain->resize(projection_matrix);
        floor->resize(projection_matrix);
        bull->resize(projection_matrix);
        statue->resize(projection_matrix);

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
        
    }
}
