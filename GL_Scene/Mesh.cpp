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
            
            size_t number_of_vertices = mesh->mNumVertices;
            size_t number_of_indices;
            
            glGenBuffers(VBO_COUNT, vbo_ids);
            glGenVertexArrays(1, &vao_id);
            
            glBindVertexArray(vao_id);
            
            static_assert(sizeof(aiVector3D) == sizeof(glm::fvec3), "aiVector3D deberia tener tres floats");
            
            glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[COORDINATES_VBO]);
            glBufferData(GL_ARRAY_BUFFER, number_of_vertices * sizeof(aiVector3D), mesh->mVertices, GL_STATIC_DRAW);
            
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
            
            for (size_t i = 0; i < number_of_vertices; ++i)
            {
                colors.push_back(glm::vec3(0.5f, 0.5f, 0.5f));
            }
            
            glBindBuffer (GL_ARRAY_BUFFER, vbo_ids[COLORS_VBO]);
            glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);
            
            glEnableVertexAttribArray(1);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

            for (unsigned int j = 0; j < mesh->mNumVertices; ++j)
            {
                aiVector3D aiVertex = mesh->mVertices[j];
                coordinates.push_back(glm::vec3(aiVertex.x, aiVertex.y, aiVertex.z));
            }
            
            for (unsigned int j = 0; j < mesh->mNumFaces; ++j)
            {
                aiFace & face = mesh->mFaces[j];
                for (unsigned int k = 0; k < face.mNumIndices; ++k)
                {
                    indices.push_back(face.mIndices[k]);
                }
            }
            
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_ids[INDEXES_VBO]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
        }
        std::cout << scene->mNumMeshes << " meshes loaded." << std::endl;
    }
    
    /**
     *@brief Crea una malla utilizando las coordenadas, colores e indices de la propia clase
     *
     *@param mesh_name Nombre de la malla
     */

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

        // Crear el VBO para los colores
        glBindBuffer(GL_ARRAY_BUFFER, vbo_ids[COLORS_VBO]);
        glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), colors.data(), GL_STATIC_DRAW);
        check_gl_error("glBufferData (COLORS_VBO)");

        glEnableVertexAttribArray(1);
        check_gl_error("glEnableVertexAttribArray (COLORS_VBO)");

        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
        check_gl_error("glVertexAttribPointer (COLORS_VBO)");

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

    /**
     *@brief Función de renderizado de la malla en el bucle principal
     */
    void Mesh::render()
    {
        // std::cout << "Rendering mesh..." << std::endl;
        
        if (m_shader->has_textures())
        {
            m_shader->use();
        }
        
        glBindVertexArray (vao_id);
        
        if (m_mesh_type == MeshType::TERRAIN)
        {
            glDrawElements(GL_LINE_STRIP, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
        }
        else
        {
            glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indices.size()), GL_UNSIGNED_INT, 0);
        }
        glBindVertexArray (0);
    }

    void Mesh::set_shader( std::unique_ptr < udit::Shader > shader)
    {
        if (shader != nullptr)
        {
            m_shader = std::move(shader);
        }
    }

    std::pair < GLint, GLint > Mesh::get_shader_matrix_ids()
    {
        return std::make_pair(m_shader->get_model_view_matrix_id(), m_shader->get_projection_matrix_id());
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
