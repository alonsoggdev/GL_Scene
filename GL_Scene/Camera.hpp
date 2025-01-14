//
//  Camera.hpp
//  GL_Scene
//
//  Created by Alonso García on 23/12/24.
//

#pragma once

#include "glm.hpp"
#include <gtc/matrix_transform.hpp>
#include <gtc/constants.hpp>

enum class CameraMovement
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
/**
 * @class Camera
 * @brief Clase que gestiona la cámara en un entorno 3D, incluyendo el control de la posición,
 *        orientación y el movimiento de la cámara.
 *
 * La clase `Camera` permite controlar la vista desde una cámara en 3D, proporcionando
 * funcionalidades para mover la cámara en el espacio (adelante, atrás, izquierda, derecha, etc.),
 * así como ajustar su orientación y zoom. Es comúnmente utilizada en aplicaciones gráficas en 3D,
 * como videojuegos o simulaciones, donde se necesita un control interactivo sobre la vista de la escena.
 */
class Camera
{
public:
    /**
     * @brief Posición actual de la cámara.
     *
     * Esta es la posición de la cámara en el espacio 3D.
     */
    glm::vec3 position;

    /**
     * @brief Dirección hacia la cual está mirando la cámara.
     *
     * Define la dirección en la que la cámara está mirando. Esto se utiliza para calcular
     * la matriz de vista de la cámara.
     */
    glm::vec3 front;

    /**
     * @brief Vectores de orientación de la cámara en el eje Y (arriba).
     *
     * Define la dirección del "arriba" de la cámara, utilizado para la orientación de la vista.
     */
    glm::vec3 up;

    /**
     * @brief Vectores de la orientación de la cámara en el eje X (derecha).
     *
     * Define la dirección "derecha" de la cámara. Este vector es calculado en función del
     * eje 'up' y 'front'.
     */
    glm::vec3 right;

    /**
     * @brief Dirección "arriba" global.
     *
     * Este es el vector global de "arriba" que se utiliza para la rotación de la cámara
     * para mantener la orientación correcta de la cámara.
     */
    glm::vec3 world_up;
    
    /**
     * @brief Ángulo de orientación de la cámara alrededor del eje Y.
     *
     * El ángulo de giro (yaw) se utiliza para girar la cámara alrededor del eje vertical.
     */
    float yaw;

    /**
     * @brief Ángulo de orientación de la cámara alrededor del eje X.
     *
     * El ángulo de inclinación (pitch) controla la rotación de la cámara alrededor del eje horizontal.
     */
    float pitch;
    
    /**
     * @brief Velocidad de movimiento de la cámara.
     *
     * Define la rapidez con la que la cámara se mueve en función del delta_time.
     */
    float movement_speed;

    /**
     * @brief Sensibilidad al movimiento del ratón.
     *
     * Controla cuánto se ajustan los ángulos de yaw y pitch cuando se mueve el ratón.
     */
    float mouse_sensitivity;

    /**
     * @brief Nivel de zoom de la cámara.
     *
     * Representa el zoom de la cámara, determinando el campo de visión (FOV).
     */
    float zoom;

    /**
     * @brief Constructor de la cámara.
     *
     * Inicializa una nueva cámara con la posición, dirección "arriba", yaw y pitch especificados.
     *
     * @param start_position La posición inicial de la cámara en el espacio 3D.
     * @param up_direction La dirección "arriba" de la cámara.
     * @param start_yaw El ángulo de yaw inicial de la cámara.
     * @param start_pitch El ángulo de pitch inicial de la cámara.
     */
    Camera(glm::vec3 start_position, glm::vec3 up_direction, float start_yaw, float start_pitch);

    /**
     * @brief Obtiene la matriz de vista de la cámara.
     *
     * La matriz de vista se usa para transformar las coordenadas de la escena en relación con
     * la posición y orientación de la cámara.
     *
     * @return Una matriz 4x4 que representa la vista de la cámara.
     */
    glm::mat4 get_view_matrix() const;

    /**
     * @brief Procesa la entrada de teclado para mover la cámara.
     *
     * Cambia la posición de la cámara según la dirección especificada y el delta_time dado.
     * El delta_time es usado para ajustar el movimiento en función del tiempo transcurrido.
     *
     * @param direction La dirección en la que se desea mover la cámara (adelante, atrás, izquierda, derecha, etc.).
     * @param delta_time El tiempo transcurrido desde el último fotograma, usado para controlar la velocidad.
     */
    void process_keyboard(CameraMovement direction, float delta_time);

    /**
     * @brief Procesa el movimiento del ratón para rotar la cámara.
     *
     * Ajusta la orientación de la cámara en función de los movimientos del ratón. La sensibilidad
     * de estos movimientos es controlada por el valor de `mouse_sensitivity`.
     *
     * @param x_offset El cambio en la posición X del ratón.
     * @param y_offset El cambio en la posición Y del ratón.
     * @param constraint_pitch Si se debe restringir el ángulo de pitch para evitar una rotación excesiva.
     */
    void process_mouse_movement(float x_offset, float y_offset, bool constraint_pitch = true);

private:
    /**
     * @brief Actualiza los vectores de la cámara (front, up, right).
     *
     * Calcula los vectores de la cámara (front, up, right) en función de los ángulos de yaw y pitch,
     * para asegurar que la orientación de la cámara sea correcta en todo momento.
     */
    void update_camera_vectors();
};
