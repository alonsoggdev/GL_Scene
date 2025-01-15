//
//  Cube.hpp
//  GL_Geometry
//
//  Created by Alonso García on 21/12/24.
//

#pragma once

#include "glad.h"

#include "Mesh.hpp"

/**
 * @class Cube
 * @brief Clase que representa un cubo, heredando de la clase `Mesh`.
 *
 * La clase `Cube` crea y gestiona un cubo 3D. Ofrece constructores para crear un cubo con un
 * tamaño específico y con la opción de invertir las normales (útil para crear un Skybox, por ejemplo). Hereda de la clase `Mesh`..
 */
namespace udit
{
    class Cube : public Mesh
    {
    private:
        /**
         * @brief Tamaño del cubo.
         *
         * Representa el tamaño de los lados del cubo. Un valor mayor genera un cubo más grande.
         */
        float size;

    public:
        /**
         * @brief Constructor por defecto.
         *
         * Este constructor crea un cubo con un tamaño predeterminado y sin invertir las normales.
         */
        Cube();

        /**
         * @brief Constructor con opción de invertir las normales.
         *
         * Este constructor crea un cubo con un tamaño predeterminado. La opción de invertir las normales
         * puede ser útil para efectos especiales como la renderización por dentro del cubo.
         *
         * @param inverted Si es `true`, las normales del cubo se invierten.
         */
        Cube(bool inverted);

        /**
         * @brief Constructor con tamaño especificado.
         *
         * Este constructor crea un cubo con un tamaño determinado y sin invertir las normales.
         *
         * @param size El tamaño de los lados del cubo.
         */
        Cube(float size);

        /**
         * @brief Constructor con tamaño y opción de invertir las normales.
         *
         * Este constructor permite crear un cubo de cualquier tamaño, con la opción de invertir las normales.
         * La inversión de las normales puede ser útil para representar el cubo desde dentro.
         *
         * @param size El tamaño de los lados del cubo.
         * @param inverted Si es `true`, las normales del cubo se invierten.
         */
        Cube(float size, bool inverted);

    private:
        /**
         * @brief Crea un cubo con las características especificadas.
         *
         * Esta función genera la maya del cubo con un tamaño y las posibles modificaciones sobre las normales.
         * Si las normales son invertidas, el cubo se renderizará desde el interior.
         *
         * @param inverted Si es `true`, las normales del cubo se invierten.
         */
        void create_cube(bool inverted = false);
    };
}
