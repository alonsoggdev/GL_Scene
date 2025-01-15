//
//  NewLight.hpp
//  GL_Scene
//
//  Created by Alonso García on 13/1/25.
//

#pragma once

#include "glm.hpp"
#include <iostream>

#include "Cube.hpp"

namespace udit
{
    /**
     * @class Light
     * @brief Clase que representa una fuente de luz en la escena.
     *
     * La clase `Light` es responsable de definir las características básicas de una fuente de luz,
     * tales como su posición, color y las intensidades de la luz ambiental y difusa. Esta clase
     * se utiliza para enviar la información de la luz a los shaders en OpenGL para que los efectos de luz
     * sean aplicados en la escena 3D.
     */
    class Light {
    private:
        /**
         * @brief Posición de la fuente de luz en el espacio 3D.
         */
        glm::vec3 position;

        /**
         * @brief Color de la fuente de luz (RGB).
         */
        glm::vec3 color;

        /**
         * @brief Intensidad de la luz ambiental.
         *
         * La luz ambiental ilumina uniformemente todas las superficies, sin importar su orientación o distancia.
         */
        float ambientIntensity;

        /**
         * @brief Intensidad de la luz difusa.
         *
         * La luz difusa se dispersa en todas direcciones, afectando la superficie de manera más realista
         * según su orientación respecto a la fuente de luz.
         */
        float diffuseIntensity;

    public:
        /**
         * @brief Constructor de la clase Light.
         *
         * Este constructor inicializa los parámetros de la luz con valores específicos para su posición,
         * color y las intensidades de luz ambiental y difusa.
         *
         * @param pos Posición de la luz en el espacio 3D.
         * @param col Color de la luz, especificado en formato RGB.
         * @param ambient Intensidad de la luz ambiental.
         * @param diffuse Intensidad de la luz difusa.
         */
        Light(const glm::vec3& pos, const glm::vec3& col, float ambient, float diffuse);

        /**
         * @brief Crea una luz a partir de los parámetros especificados.
         *
         * Esta función estática facilita la creación de un objeto `Light` compartido (`shared_ptr`) con
         * los valores de posición, color e intensidades de luz ambiental y difusa.
         *
         * @param pos Posición de la luz en el espacio 3D.
         * @param col Color de la luz, especificado en formato RGB.
         * @param ambient Intensidad de la luz ambiental.
         * @param diffuse Intensidad de la luz difusa.
         *
         * @return Un `std::shared_ptr<Light>` que apunta a la nueva luz creada.
         */
        static std::shared_ptr <Light> make_light(const glm::vec3& pos, const glm::vec3& col, float ambient, float diffuse);

        /**
         * @brief Envía los parámetros de la luz al shader.
         *
         * Esta función toma los parámetros de la luz (posición, color, intensidad) y los envía al
         * shader especificado a través de su programa de OpenGL. Esto permite que la luz sea utilizada
         * en los cálculos de sombreado dentro del pipeline de gráficos.
         *
         * @param program_id El identificador del programa de shader de OpenGL.
         */
        void send_to_shader(GLuint program_id) const;
    };

}

