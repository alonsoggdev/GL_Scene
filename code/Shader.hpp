//
//  Shader.hpp
//  GL_Geometry
//
//  Created by Alonso García on 11/12/24.
//
/**
 * @file Shader.hpp
 * @brief Clase que representa un shader en OpenGL, gestionando la compilación y uso de programas de sombreado.
 *
 * La clase `Shader` gestiona la creación, compilación y uso de shaders en OpenGL, incluyendo
 * tanto el vertex shader como el fragment shader. Además, permite la gestión de texturas asociadas
 * al shader y la configuración de matrices para la proyección, vista y normales en el contexto de la cámara.
 */

#pragma once

#include <iostream>
#include "glad.h"
#include "Texture.hpp"

namespace udit
{
    /**
     * @enum ShaderType
     * @brief Enumeración que define los diferentes tipos de shaders.
     *
     * Define los tipos de shaders que la clase `Shader` puede usar para diferentes
     * efectos visuales, como el skybox, geometría, textura única, terreno y por defecto.
     */
    enum class ShaderType
    {
        SKYBOX,      /**< Shader para el skybox. */
        GEOMETRY,    /**< Shader para la geometría. */
        SINGLE_TEXTURE, /**< Shader para una textura única. */
        TERRAIN,     /**< Shader para el terreno. */
        DEFAULT      /**< Shader por defecto. */
    };

    /**
     * @class Shader
     * @brief Representa un shader program en OpenGL.
     *
     * La clase `Shader` gestiona la creación y uso de programas de sombreado en OpenGL.
     * Permite compilar los shaders, vincularlos en un programa y usarlos para renderizar
     * objetos en la escena. También proporciona funciones para gestionar texturas y matrices
     * de transformación, como la matriz de modelo-vista, proyección y normales.
     */
    class Shader
    {
    private:
        /** @brief Identificador del programa de shader en OpenGL. */
        GLuint program_id;

        /** @brief Tipo de shader (skybox, geometría, etc.). */
        ShaderType m_type;

        /** @brief Nombre del shader. */
        std::string m_name;

        /** @brief Fuente del vertex shader especificada. */
        std::string m_vertex_source;

        /** @brief Fuente del fragment shader especificada. */
        std::string m_fragment_source;

        /** @brief Identificadores para las matrices del shader. */
        GLint  model_view_matrix_id;
        GLint  projection_matrix_id;
        GLint  normal_matrix_id;

        /** @brief Código por defecto para los shaders. */
        static const std::string    default_vertex_shader_code;
        static const std::string    default_fragment_shader_code;

        /** @brief Texturas asociadas al shader. */
        std::vector <std::shared_ptr<Texture>> textures;

    public:
        /**
         * @brief Constructor por defecto.
         *
         * Crea un objeto `Shader` sin especificar un tipo o fuentes de shader. Este constructor
         * generalmente se usa para crear shaders más tarde con la función `make_shader`.
         */
        Shader();

        /**
         * @brief Constructor para crear un shader con tipos y fuentes especificadas.
         *
         * @param type Tipo de shader (e.g., SKYBOX, GEOMETRY).
         * @param vertex_source Código fuente para el vertex shader.
         * @param fragment_source Código fuente para el fragment shader.
         * @param name Nombre del shader.
         */
        Shader(ShaderType type, const std::string & vertex_source, const std::string & fragment_source, const std::string & name);

        /**
         * @brief Destructor.
         *
         * Libera los recursos asociados al shader.
         */
        ~Shader();

        /**
         * @brief Crea un shader.
         *
         * Función estática para crear un shader con un tipo específico y fuentes de shader opcionales.
         * @param type Tipo de shader.
         * @param vertex_shader Código fuente del vertex shader.
         * @param fragment_shader Código fuente del fragment shader.
         * @param texture_paths Rutas a las texturas asociadas.
         * @param name Nombre del shader.
         * @return Objeto `Shader` creado.
         */
        static std::shared_ptr < Shader > make_shader(
            udit::ShaderType type = udit::ShaderType::DEFAULT,
            const std::string & vertex_shader = "",
            const std::string & fragment_shader = "",
            const std::vector<std::string> & texture_paths = {""},
            const std::string & name = ""
        );

        /**
         * @brief Compila los shaders.
         *
         * Compila un vertex shader y un fragment shader usando el código fuente proporcionado.
         * @param vertex_shader_code Código fuente del vertex shader.
         * @param fragment_shader_code Código fuente del fragment shader.
         * @return Identificador del programa de shader compilado.
         */
        GLuint compile_shaders(const char * vertex_shader_code, const char * fragment_shader_code);

        /**
         * @brief Obtiene el identificador de la matriz de modelo-vista.
         * @return Identificador de la matriz de modelo-vista.
         */
        GLint get_model_view_matrix_id() { return model_view_matrix_id; }

        /**
         * @brief Obtiene el identificador de la matriz de proyección.
         * @return Identificador de la matriz de proyección.
         */
        GLint get_projection_matrix_id() { return projection_matrix_id; }

        /**
         * @brief Obtiene el identificador de la matriz de normales.
         * @return Identificador de la matriz de normales.
         */
        GLint get_normal_matrix_id() { return normal_matrix_id; }

        /**
         * @brief Obtiene el identificador del programa de shader.
         * @return Identificador del programa de shader.
         */
        GLuint get_program_id() const { return program_id; }

        /**
         * @brief Establece una textura para el shader.
         *
         * @param texture Puntero a la textura que será asignada al shader.
         */
        void set_texture(const std::shared_ptr<Texture> & texture);

        /**
         * @brief Activa y usa el programa de shader.
         *
         * Hace que el programa de shader sea el activo para su uso en la siguiente operación de renderizado.
         */
        void use() const;

        /**
         * @brief Establece la escala de las texturas asociadas al shader.
         * @param scale Factor de escala para las texturas.
         */
        void set_texture_scale(float scale);

        /**
         * @brief Verifica si el shader tiene texturas asociadas.
         * @return `true` si el shader tiene texturas asociadas, `false` en caso contrario.
         */
        bool has_textures() { return !textures.empty(); }

        /**
         * @brief Establece el nombre del shader.
         * @param name Nombre del shader.
         */
        void set_name(const std::string & name) { m_name = name; }

        /**
         * @brief Obtiene el nombre del shader.
         * @return Nombre del shader.
         */
        std::string get_name() { return m_name; }

    private:
        /**
         * @brief Muestra los errores de compilación de un shader.
         * @param shader_id Identificador del shader.
         */
        void show_compilation_error(GLuint shader_id);

        /**
         * @brief Muestra los errores de enlace del programa de shader.
         * @param program_id Identificador del programa de shader.
         */
        void show_linkage_error(GLuint program_id);
    };
}
