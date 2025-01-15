//
//  Skybox.hpp
//  GL_Scene
//
//  Created by Alonso García on 21/12/24.
//
/**
 * @file Skybox.hpp
 * @brief Clase para representar y gestionar un skybox en OpenGL.
 *
 * La clase `Skybox` hereda de `Cube` y permite la carga y visualización de un cubo que actúa
 * como el fondo de la escena, utilizando una serie de texturas que representan las caras del cielo.
 * Se utiliza para crear una atmósfera inmersiva en la escena renderizada.
 */

#pragma once

#include "Cube.hpp"
#include <vector>
#include <string>

namespace udit
{
    /**
     * @class Skybox
     * @brief Representa un skybox, un cubo con texturas aplicadas en sus seis caras.
     *
     * Un skybox es un cubo que rodea la escena y sirve como fondo inmersivo en un entorno 3D.
     * La clase `Skybox` hereda de la clase `Cube`, y se encarga de cargar las texturas y
     * mostrar el cielo en una escena utilizando un cubo con caras texturizadas.
     */
    class Skybox : public Cube
    {
    private:
        /** @brief Identificador de la textura del cubo (cubemap) que representa el skybox. */
        unsigned int cubemapTexture;

        /** @brief Ruta a las texturas de las caras del skybox. */
        std::string filepath = "/Users/alonsoggdev/UDIT/Asignaturas/Programacion_Grafica/GL_Scene/resources/skybox/";

    public:
        /**
         * @brief Constructor por defecto.
         *
         * Este constructor crea un skybox con un tamaño por defecto y sin texturas cargadas.
         */
        Skybox();

        /**
         * @brief Constructor que permite especificar el tamaño y las texturas del skybox.
         *
         * @param size Tamaño del cubo que representará el skybox.
         * @param faces Vector de rutas a las texturas que serán aplicadas a las caras del skybox.
         */
        Skybox(float size, const std::vector<std::string>& faces);

        /**
         * @brief Obtiene el identificador de la textura cubemap cargada para el skybox.
         *
         * @return Identificador de la textura cubemap.
         */
        unsigned int getCubemapTexture() const { return cubemapTexture; }

    private:
        /**
         * @brief Carga las texturas de las caras del skybox.
         *
         * Esta función se encarga de cargar las texturas especificadas en las rutas proporcionadas
         * en el vector `faces`. Las texturas se aplican a las seis caras del cubo que representa
         * el skybox.
         *
         * @param faces Vector de rutas a las texturas de las seis caras del skybox.
         */
        void loadCubemap(const std::vector<std::string>& faces);
    };
}
