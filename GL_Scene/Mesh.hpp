//
//  Mesh.hpp
//  GL_Geometry
//
//  Created by Alonso García on 11/12/24.
//

#pragma once

#include <vector>

#include "glm.hpp"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "glad.h"

#include "Shader.hpp"

namespace udit
{
    enum class MeshType
    {
        BASIC,
        MESH,
        TERRAIN,
        SKYBOX
    };

    /**
     * @class Mesh
     * @brief Clase que representa una malla 3D.
     *
     * La clase `Mesh` es la base para representar mallas 3D en OpenGL. Contiene todos los atributos y
     * funciones necesarias para cargar, gestionar y renderizar mallas con vértices, normales, colores,
     * coordenadas de textura y los índices que definen la topología de la malla. Esta clase también incluye
     * funciones para transformar la malla (traslación, rotación, escala) y para actualizar y renderizar la malla
     * en la escena.
     */
    class Mesh
    {
    private:
        /**
         * @brief Enumeración que define los tipos de malla soportados.
         */
        enum
        {
            COORDINATES_VBO,    ///< VBO para las coordenadas de los vértices.
            COLORS_VBO,         ///< VBO para los colores de los vértices.
            NORMALS_VBO,        ///< VBO para las normales de los vértices.
            INDEXES_VBO,        ///< VBO para los índices de los vértices.
            TEXTURE_UV_VBO,     ///< VBO para las coordenadas de textura.
            VBO_COUNT           ///< Número total de VBOs.
        };

        /**
         * @brief Tipo de malla, que define el tipo de geometría.
         */
        MeshType m_mesh_type;

    protected:
        /**
         * @brief Vectores que almacenan las coordenadas de los vértices, colores, normales, índices y coordenadas de textura.
         */
        std::vector<glm::vec3> coordinates;
        std::vector<glm::vec3> colors;
        std::vector<glm::vec3> normals;
        std::vector<GLuint> indices;
        std::vector<glm::vec2> texture_uvs;

        /**
         * @brief Número total de vértices de la malla.
         */
        GLsizei number_of_vertices;

        /**
         * @brief Crea los VBOs y el VAO necesarios para la malla.
         *
         * @param mesh_name Nombre de la malla a crear.
         */
        void create_mesh(std::string mesh_name = "");

    private:
        /**
         * @brief IDs de los VBOs y VAO.
         */
        GLuint vbo_ids[VBO_COUNT];
        GLuint vao_id;

        /**
         * @brief Matrices de transformación de la malla.
         */
        glm::mat4 model_view_matrix;
        glm::mat4 normal_matrix;
        
        /**
         * @brief Angulo de rotacion.
         */
        float angle;

        /**
         * @brief Shader asociado a la malla.
         */
        std::shared_ptr < udit::Shader > m_shader;

    public:
        /**
         * @brief Constructor por defecto.
         */
        Mesh();

        /**
         * @brief Constructor que carga una malla desde un archivo.
         *
         * Este constructor carga los datos de la malla (coordenadas, normales, colores, etc.)
         * desde un archivo y los almacena en los atributos correspondientes.
         *
         * @param path Ruta al archivo que contiene la malla.
         */
        Mesh(std::string & path);

        /**
         * @brief Crea una malla de un tipo específico.
         *
         * Este método estático permite crear una malla de un tipo específico, como terreno, malla básica,
         * o malla cargada desde un archivo.
         *
         * @param type Tipo de malla a crear.
         * @param path Ruta al archivo de la malla (solo relevante si el tipo es MESH).
         * @return Un puntero compartido a la malla creada.
         */
        static std::shared_ptr <Mesh> make_mesh(MeshType type, const std::string &path = "");

        /**
         * @brief Destructor de la clase.
         *
         * El destructor limpia los recursos de OpenGL, como los buffers y el VAO.
         */
        virtual ~Mesh();

        /**
         * @brief Realiza una traslación de la malla.
         *
         * Aplica una traslación a la matriz de transformación de la malla.
         *
         * @param translation Vector de traslación.
         */
        virtual void translate(glm::vec3 translation);

        /**
         * @brief Rota la malla.
         *
         * Aplica una rotación a la matriz de transformación de la malla.
         *
         * @param rotation Eje de rotación.
         * @param angle Ángulo de rotación en grados.
         */
        virtual void rotate(glm::vec3 rotation, float angle);
        /**
         * @brief Orbita la malla alrededor de un punto.
         *
         * Aplica una trayectoria de orbita.
         *
         * @param center Punto central de orbita.
         * @param distance Distancia al punto central.
         * @param speed Velocidad de orbita
         */
        virtual void orbit(glm::vec3 center, float distance, float speed);

        /**
         * @brief Escala la malla.
         *
         * Aplica una escala a la matriz de transformación de la malla.
         *
         * @param scale Factor de escala.
         */
        virtual void scale(glm::vec3 scale);

        /**
         * @brief Actualiza la malla.
         *
         * Esta función puede ser utilizada para actualizar los datos de la malla, si es necesario.
         */
        virtual void update();

        /**
         * @brief Renderiza la malla.
         *
         * Utiliza el shader asociado y la matriz de vista para renderizar la malla.
         *
         * @param view_matrix Matriz de vista.
         */
        virtual void render(glm::mat4 view_matrix);

        /**
         * @brief Ajusta la matriz de proyección.
         *
         * Establece la matriz de proyección en el shader para la correcta visualización.
         *
         * @param projection_matrix Matriz de proyección.
         */
        virtual void resize(glm::mat4 projection_matrix);

        /**
         * @brief Asocia un shader a la malla.
         *
         * Permite asociar un shader para ser usado al renderizar la malla.
         *
         * @param shader Puntero al shader a asociar.
         */
        virtual void set_shader(std::shared_ptr < udit::Shader > shader);

        /**
         * @brief Obtiene el ID del programa del shader asociado.
         *
         * @return El ID del programa de shader asociado a la malla.
         */
        GLuint get_shader_program_id() const;

        /**
         * @brief Obtiene los IDs de las matrices del shader asociadas a la malla.
         *
         * Devuelve los IDs de las matrices necesarias para renderizar la malla en el shader.
         *
         * @return Un vector con los IDs de las matrices.
         */
        std::vector < GLint > get_shader_matrix_ids();

        /**
         * @brief Obtiene la matriz de transformación del modelo.
         *
         * @return La matriz de transformación del modelo.
         */
        glm::mat4 get_model_view_matrix() const { return model_view_matrix; }

        /**
         * @brief Establece la matriz de transformación del modelo.
         *
         * @param matrix Nueva matriz de transformación del modelo.
         */
        void set_model_view_matrix(glm::mat4 matrix) { model_view_matrix = matrix; }

        /**
         * @brief Establece el tipo de malla.
         *
         * @param type Tipo de malla.
         */
        void set_mesh_type(MeshType type) { m_mesh_type = type; }
    };

}
