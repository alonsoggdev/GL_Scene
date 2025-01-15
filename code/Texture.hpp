//
//  Texture.hpp
//  GL_Scene
//
//  Created by Alonso García on 24/12/24.
//
/**
 * @file Texture.hpp
 * @brief Clase para gestionar las texturas en OpenGL.
 *
 * La clase `Texture` permite la carga, enlace y liberación de texturas en OpenGL.
 * Se utiliza para manejar imágenes que se aplican a los objetos 3D en la escena, permitiendo
 * efectos visuales como color, relieve, etc.
 */

#pragma once

#include <string>
#include <glad.h>

namespace udit
{
    /**
     * @enum Texture_Type
     * @brief Enum que define los tipos de texturas disponibles.
     *
     * Los tipos de texturas permiten diferenciar entre distintos tipos de efectos visuales:
     * - `COLOR`: Textura normal, utilizada para representar colores o imágenes en 3D.
     * - `HEIGHT`: Textura de altura, generalmente utilizada en mapas de relieve.
     */
    enum class Texture_Type
    {
        COLOR,  /**< Textura de color (imagen normal). */
        HEIGHT  /**< Textura de altura (mapa de relieve). */
    };

    /**
     * @class Texture
     * @brief Representa una textura en OpenGL.
     *
     * La clase `Texture` permite la carga y manejo de texturas en OpenGL. Estas texturas pueden
     * ser utilizadas en diferentes tipos de materiales y objetos 3D dentro de la escena.
     * La clase gestiona el enlace y des-enlace de texturas, permitiendo su uso en shaders.
     */
    class Texture
    {
    private:
        /** @brief Indicador de si la textura ha sido cargada exitosamente. */
        bool loaded = false;

        /** @brief Tipo de textura (Color o Altura). */
        Texture_Type m_type;

    public:
        /**
         * @brief Constructor que crea la textura a partir de un archivo.
         *
         * Este constructor carga la textura desde una ruta de archivo específica. Se puede
         * especificar el tipo de textura (por defecto es COLOR).
         *
         * @param path Ruta al archivo de la textura (imagen).
         * @param texture_unit Unidad de textura (GL_TEXTURE0, GL_TEXTURE1, etc.).
         * @param type Tipo de la textura (por defecto COLOR).
         */
        Texture(const std::string & path, GLenum texture_unit, Texture_Type type = Texture_Type::COLOR);

        /** @brief Destructor que libera la textura cargada. */
        ~Texture();
        
        /**
         * @brief Enlaza la textura a la unidad de textura actual.
         *
         * Este método enlaza la textura al contexto de OpenGL, permitiendo que sea utilizada
         * por los shaders para renderizar objetos con la textura aplicada.
         */
        void bind() const;

        /**
         * @brief Desenlaza la textura de la unidad de textura.
         *
         * Este método desenlaza la textura, liberando la unidad de textura para ser utilizada
         * por otras texturas.
         */
        void unbind() const;

        /** @brief Identificador de la textura cargada. */
        GLuint texture_id;

        /** @brief Unidad de textura a la que la textura está asignada. */
        GLenum texture_unit;

        /** @brief Ruta del archivo de la textura. */
        std::string file_path;
        
        /**
         * @brief Carga la textura desde el archivo especificado.
         *
         * Este método lee el archivo de imagen y crea una textura en OpenGL.
         * Se encarga de configurar los parámetros y cargar la imagen a la memoria de GPU.
         */
        void load_texture();

        /**
         * @brief Establece el tipo de la textura (COLOR o HEIGHT).
         *
         * @param type Tipo de la textura a establecer.
         */
        void set_type(Texture_Type type) { m_type = type; }

        /**
         * @brief Indica si la textura ha sido cargada exitosamente.
         *
         * @return true si la textura ha sido cargada, false en caso contrario.
         */
        bool is_loaded() { return loaded; }
    };
}

