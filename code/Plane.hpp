//
//  Plane.hpp
//  GL_Geometry
//
//  Created by Alonso García on 11/12/24.
//

#pragma once

#include "glad.h"

#include "Mesh.hpp"

namespace udit
{
    /**
     * @class Plane
     * @brief Clase que representa un plano 3D.
     *
     * La clase `Plane` hereda de `Mesh` y está diseñada para representar un plano 3D en OpenGL. El plano se define
     * por su ancho, altura, y la cantidad de columnas y filas que tiene. Esta clase permite crear un plano con
     * diferentes configuraciones, ya sea con un tamaño específico o con una distribución de vértices más compleja.
     * El plano es útil para representar superficies planas, como terrenos o fondos.
     */
    class Plane : public Mesh
    {
    private:
        /**
         * @brief Ancho del plano.
         */
        float width;

        /**
         * @brief Alto del plano.
         */
        float height;

        /**
         * @brief Número de columnas del plano.
         */
        unsigned columns;

        /**
         * @brief Número de filas del plano.
         */
        unsigned rows;

    public:
        /**
         * @brief Constructor por defecto.
         *
         * Crea un plano con dimensiones predeterminadas.
         */
        Plane();

        /**
         * @brief Constructor que define el tamaño del plano.
         *
         * Crea un plano cuadrado con el tamaño especificado.
         *
         * @param size Tamaño del plano en ambas dimensiones (ancho y alto).
         */
        Plane(float size);

        /**
         * @brief Constructor que define el tamaño y la resolución del plano.
         *
         * Crea un plano con el tamaño y la cantidad de columnas y filas especificados.
         *
         * @param width Ancho del plano.
         * @param height Alto del plano.
         * @param columns Número de columnas del plano (resolución horizontal).
         * @param rows Número de filas del plano (resolución vertical).
         */
        Plane(float width, float height, unsigned columns, unsigned rows);

    private:
        /**
         * @brief Crea los VBOs y el VAO necesarios para representar el plano.
         *
         * Esta función genera la geometría del plano, creando los buffers necesarios para representar
         * las coordenadas, colores, normales y coordenadas de textura, así como el VAO correspondiente.
         */
        void create_plane();
    };

}
