//
//  Scene.hpp
//  GL_Geometry
//
//  Created by Alonso García on 9/12/24.
//
/**
 * @file Scene.hpp
 * @brief Clase que representa una escena 3D, gestionando objetos como el fondo, terreno, luz, etc.
 *
 * Esta clase es responsable de mantener y gestionar la escena 3D, incluyendo el fondo (skybox),
 * el terreno, las luces y el resto de elementos gráficos. Permite actualizar, renderizar y redimensionar
 * la escena, además de configurar las matrices de vista y proyección, y la luz del entorno.
 */

#pragma once

#include <string>
#include "Shader.hpp"
#include "Light.hpp"
#include "Skybox.hpp"
#include "Plane.hpp"

namespace udit
{
    /**
     * @class Scene
     * @brief Representa una escena 3D con un skybox, terreno, luz y otros elementos.
     *
     * La clase `Scene` es responsable de gestionar la representación de una escena 3D,
     * incluyendo los objetos gráficos principales y la iluminación. Los métodos permiten
     * actualizar la escena, renderizarla y ajustar su tamaño.
     */
    class Scene
    {
    private:
        /**
         * @brief Lista de las texturas del skybox (caras).
         *
         * Esta lista contiene los nombres de las texturas que serán cargadas para las caras
         * del skybox, representando el entorno.
         */
        std::vector<std::string> skybox_faces =
        {
               "skybox_east.jpg", "skybox_west.jpg", "skybox_up.jpg",
               "skybox_down.jpg", "skybox_north.jpg", "skybox_south.jpg"
        };
        
        /** @brief Ángulo de rotación para la escena. */
        float angle = 0.0f;
        
        /** @brief Objeto skybox que representa el fondo de la escena. */
        std::shared_ptr<Skybox> skybox;

        /** @brief Terreno (plane) de la escena. */
        std::shared_ptr<Plane> terrain;
        
        /** @brief Piso (plane) de la escena. */
        std::shared_ptr<Plane> floor;
        
        /** @brief Malla (mesh) de un objeto, escultura de toro. */
        std::shared_ptr<Mesh> bull;
        
        /** @brief Malla (mesh) de un objeto, estatua de buda. */
        std::shared_ptr<Mesh> statue;
        
        /** @brief Malla (mesh) de un objeto, coche */
        std::shared_ptr<Mesh> car;
        
        /** @brief Luz de la escena. */
        std::shared_ptr<Light> light;
        
        /** @brief Ancho de la ventana de renderizado. */
        unsigned width, height;
        
        /** @brief Matriz de vista para la cámara. */
        glm::mat4 view_matrix;

        /** @brief Matriz de proyección de la cámara. */
        glm::mat4 projection_matrix;
        
    public:
        /**
         * @brief Constructor de la escena.
         *
         * Inicializa una nueva escena con el ancho y alto especificados.
         * @param width Ancho de la ventana de renderizado.
         * @param height Alto de la ventana de renderizado.
         */
        Scene(unsigned width, unsigned height);

        /**
         * @brief Actualiza la escena.
         *
         * Llama a las funciones necesarias para actualizar los objetos en la escena.
         * Este método debe ser llamado cada vez que se desea actualizar el estado de la escena.
         */
        void update();

        /**
         * @brief Renderiza la escena.
         *
         * Dibuja todos los elementos de la escena (skybox, terreno, objetos, luz) en la ventana de renderizado.
         * Este método debe ser llamado en cada ciclo de renderizado.
         */
        void render();

        /**
         * @brief Redimensiona la escena.
         *
         * Ajusta la escena al nuevo tamaño de la ventana.
         * @param width Nuevo ancho de la ventana.
         * @param height Nuevo alto de la ventana.
         */
        void resize(unsigned width, unsigned height);

        /**
         * @brief Establece la matriz de vista para la cámara.
         *
         * Establece la matriz de vista que será usada para renderizar la escena.
         * @param view Matriz de vista.
         */
        void set_view_matrix(const glm::mat4& view);

        /**
         * @brief Establece la matriz de proyección para la cámara.
         *
         * Establece la matriz de proyección que será usada para renderizar la escena.
         * @param projection Matriz de proyección.
         */
        void set_projection_matrix(const glm::mat4& projection);

        /**
         * @brief Establece las luces en el shader.
         *
         * Configura las luces de la escena dentro del shader, enviando los parámetros necesarios
         * al programa de sombreado.
         * @param shader_program_id Identificador del programa de sombreado (shader).
         */
        void set_lights(GLuint shader_program_id);
    };
}
