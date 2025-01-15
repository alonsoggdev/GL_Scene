//
//  Mesh.cpp
//  GL_Geometry
//
//  Created by Alonso García on 11/12/24.
//

#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.hpp"
#include "Plane.hpp"
#include "Skybox.hpp"

#include <cassert>

using udit::Mesh;

namespace udit
{
    /**
     *@brief Constructor por defecto
     */
    Mesh::Mesh()
    {
        
    }

    Mesh::Mesh(std::string & path)
    {
        m_mesh_type = MeshType::MESH;
        Assimp::Importer importer;
        std::cout << "Loading mesh from " << path << std::endl;
        const aiScene * scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
        
        if (!scene || !scene->HasMeshes())
        {
            std::cerr << "Error cargando modelo 3D: " << path << std::endl;
            return;
        }
        
        for (unsigned int i = 0; i < scene->mNumMeshes; ++i)
        {
            aiMesh * mesh = scene->mMeshes[i];
            
            // Cargar la información del mesh (coordenadas, normales, etc.)

            for (unsigned int j = 0; j < mesh->mNumVertices; ++j)
            {
                aiVector3D aiVertex = mesh->mVertices[j];
                coordinates.push_back(glm::vec3(aiVertex.x, aiVertex.y, aiVertex.z));
                
                if (mesh->HasNormals())
                {
                    aiVector3D aiNormal = mesh->mNormals[j];
                    normals.push_back(glm::vec3(aiNormal.x, aiNormal.y, aiNormal.z));
                }

                // Los colores se mantienen por defecto a gris
                colors.push_back(glm::vec3(0.5f, 0.5f, 0.5f));

                // Aquí puedes agregar la carga de coordenadas UV si las tienes
                if (mesh->mTextureCoords[0])
                {
                    aiVector3D uv = mesh->mTextureCoords[0][j];
                    texture_uvs.push_back(glm::vec2(uv.x, uv.y));
                }
                else
                {
                    texture_uvs.push_back(glm::vec2(0.0f, 0.0f));  // Si no hay coordenadas UV, asignar un valor predeterminado
                }
            }

            // Cargar los índices
            for (unsigned int j = 0; j < mesh->mNumFaces; ++j)
            {
                aiFace & face = mesh->mFaces[j];
                for (unsigned int k = 0; k < face.mNumIndices; ++k)
                {
                    indices.push_back(face.mIndices[k]);
                }
            }
        }

        std::cout << scene->mNumMeshes << " meshes loaded." << std::endl;
        
        create_mesh();
    }


    std::shared_ptr <Mesh> Mesh::make_mesh(MeshType type, const std::string &path)
    {
        std::string absolute_path = "/Users/alonsoggdev/UDIT/Asignaturas/Programacion_Grafica/GL_Scene/resources/";
        std::string relative_path = "../../../../../resources/";
        std::string complete_path = absolute_path + path;
        switch (type)
        {
            case MeshType::TERRAIN:
            case MeshType::BASIC:                
                return std::make_shared<udit::Plane>(100.0f);
            case MeshType::MESH:
                return path.empty() ? std::make_shared<udit::Mesh>()
                                    : std::make_shared<udit::Mesh>(complete_path);
            case MeshType::SKYBOX:
                std::vector<std::string> skybox_faces =
                {
                       "skybox_east.jpg", "skybox_west.jpg", "skybox_up.jpg",
                       "skybox_down.jpg", "skybox_north.jpg", "skybox_south.jpg"
                };
                return std::make_shared<udit::Skybox>(100.0f, skybox_faces);
        }
        return nullptr;
    }
    
    void check_gl_error(const std::string& function_name)
    {
        GLenum err;
        while ((err = glGetError()) != GL_NO_ERROR)
        {
            std::cout << "OpenGL error in function " << function_name << ": " << err << std::endl;
        }
    }

    void Mesh::create_mesh(std::string mesh_name)
    {
        std::cout << "Creating Mesh: " << mesh_name << std::endl;
        
        // Generar los buffers y verificar errores
        glGenBuffers(VBO_COUNT, vbo_ids);
        check_gl_error("glGenBuffers");

        glGenVertexArrays(1, &vao_id);
        check_gl_error("glGenVertexArrays");

        glBindVertexArray(vao_id);
        check_gl_error("glBindVertexArray");

        // Crear el VBO para las coordenadas
        glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[COORDINATES_VBO]);
        glBufferData(GL_ARRAY_BUFFER, coordinates.size() * sizeof(glm::vec3), coordinates.data(), GL_STATIC_DRAW);
        check_gl_error("glBufferData (COORDINATES_VBO)");

        glEnableVertexAttribArray(0);
        check_gl_error("glEnableVertexAttribArray (COORDINATES_VBO)");

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
        check_gl_error("glVertexAttribPointer (COORDINATES_VBO)");

        // Crear el VBO para las normales
        glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[NORMALS_VBO]);
        glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), normals.data(), GL_STATIC_DRAW);
        check_gl_error("glBufferData (NORMALS_VBO)");

        glEnableVertexAttribArray(2);
        check_gl_error("glEnableVertexAttribArray (NORMALS_VBO)");

        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
        check_gl_error("glVertexAttribPointer (NORMALS_VBO)");

        // Crear el VBO para los colores
        glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[COLORS_VBO]);
        glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);
        check_gl_error("glBufferData (COLORS_VBO)");

        glEnableVertexAttribArray(1);
        check_gl_error("glEnableVertexAttribArray (COLORS_VBO)");

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
        check_gl_error("glVertexAttribPointer (COLORS_VBO)");

        // Crear el VBO para las coordenadas de textura
        glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[TEXTURE_UV_VBO]);
        glBufferData(GL_ARRAY_BUFFER, texture_uvs.size() * sizeof(glm::vec2), texture_uvs.data(), GL_STATIC_DRAW);
        check_gl_error("glBufferData (TEXTURE_UV_VBO)");

        glEnableVertexAttribArray(4);
        check_gl_error("glEnableVertexAttribArray (TEXTURE_UV_VBO)");

        glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, 0, 0);
        check_gl_error("glVertexAttribPointer (TEXTURE_UV_VBO)");

        // Crear el VBO para los índices
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_ids[INDEXES_VBO]);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
        check_gl_error("glBufferData (INDEXES_VBO)");

        glBindVertexArray(0);
        check_gl_error("glBindVertexArray (0)");

        std::cout << "Mesh created successfully: " << mesh_name << std::endl;
    }


    /**
     *@brief Destructor de la clase
     */
    Mesh::~Mesh()
    {
        glDeleteVertexArrays (1, &vao_id);
        glDeleteBuffers      (VBO_COUNT, vbo_ids);
    }
    
    /**
     *@brief Función de actualizacion de la malla en el bucle principal
     */
    void Mesh::update()
    {
    }

    void Mesh::translate(glm::vec3 translation)
    {
        model_view_matrix = glm::translate(model_view_matrix, translation);
    }

    void Mesh::rotate(glm::vec3 rotation, float angle)
    {
        model_view_matrix = glm::rotate(model_view_matrix, glm::radians(angle), rotation);
    }

    void Mesh::orbit(glm::vec3 center, float distance, float speed)
    {
        angle += speed;
        if (angle > 360.0f) angle -= 360.0f;
        
        float x = distance * cos(glm::radians(angle));
        float z = distance * sin(glm::radians(angle));
        
        translate(glm::vec3(x, 0.0f, z));
        rotate(glm::vec3(0.0f, 1.0f, 0.0f), angle);
    }

    void Mesh::scale(glm::vec3 scale)
    {
        model_view_matrix = glm::scale(model_view_matrix, scale);
    }

    /**
     *@brief Función de renderizado de la malla en el bucle principal
     */
    void Mesh::render(glm::mat4 view_matrix)
    {
        // std::cout << "Rendering mesh..." << std::endl;
        m_shader->use();
        
        model_view_matrix = view_matrix * model_view_matrix;
        glUniformMatrix4fv(m_shader->get_model_view_matrix_id(), 1, GL_FALSE, glm::value_ptr(model_view_matrix));
        
        normal_matrix = glm::transpose(glm::inverse(model_view_matrix));
        glUniformMatrix4fv(m_shader->get_normal_matrix_id(), 1, GL_FALSE, glm::value_ptr(normal_matrix));

        glBindVertexArray (vao_id);
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
        glBindVertexArray (0);
    }

    void Mesh::resize(glm::mat4 projection_matrix)
    {
        glUseProgram(get_shader_program_id());
        glUniformMatrix4fv(m_shader->get_projection_matrix_id(), 1, GL_FALSE, glm::value_ptr(projection_matrix));
        glUseProgram(0);
    }

    void Mesh::set_shader(std::shared_ptr < udit::Shader > shader)
    {
        if (shader != nullptr)
        {
            m_shader = std::move(shader);
        }
    }

    std::vector < GLint > Mesh::get_shader_matrix_ids()
    {
        std::vector<GLint> ids = { m_shader->get_model_view_matrix_id(), m_shader->get_projection_matrix_id(), m_shader->get_normal_matrix_id() };
        return ids;
    }

    GLuint Mesh::get_shader_program_id() const
    {
        if (m_shader)
        {
            return m_shader->get_program_id();
        }
        else
        {
            std::cerr << "Error: No shader assigned to this mesh." << std::endl;
            return 0;
        }
    }
}
