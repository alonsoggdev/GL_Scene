//
//  EventHandler.hpp
//  GL_Scene
//
//  Created by Alonso García on 23/12/24.
//

#pragma once

#include "SDL.h"
#include "glm.hpp"
#include "Camera.hpp"

/**
 * @class EventHandler
 * @brief Clase que maneja los eventos de entrada (teclado, ratón) en la escena.
 *
 * La clase `EventHandler` es responsable de gestionar los eventos de entrada provenientes de
 * dispositivos como el teclado y el ratón. Se encarga de procesar dichos eventos y actualiza
 * la cámara en consecuencia, permitiendo la navegación a través de la escena 3D.
 */
class EventHandler
{
public:
    /**
     * @brief Constructor que inicializa el EventHandler con una referencia a la cámara.
     *
     * Este constructor inicializa el manejador de eventos con la cámara a la que se le enviarán
     * las actualizaciones. También establece valores predeterminados para el seguimiento del
     * ratón.
     *
     * @param camera La cámara que se actualizará en respuesta a los eventos.
     */
    EventHandler(Camera& camera)
        : camera(camera), first_mouse(true), last_x(0.0f), last_y(0.0f) {}

    /**
     * @brief Procesa los eventos de entrada y actualiza el estado de la cámara.
     *
     * Esta función maneja los eventos generados por el sistema (teclado, ratón) y, dependiendo
     * del tipo de evento, realiza las actualizaciones necesarias en la cámara, como moverla o
     * rotarla. Esta función debe ser llamada en cada ciclo del bucle de renderizado.
     *
     * @param running Un parámetro que indica si el bucle de la aplicación sigue en ejecución.
     *                Si se establece a `false`, el bucle terminará.
     * @param delta_time El tiempo transcurrido entre el fotograma actual y el anterior. Se utiliza
     *                   para asegurar un movimiento suave de la cámara.
     */
    void handle_events(bool & running, float delta_time);

private:
    /**
     * @brief Referencia a la cámara que se actualiza con los eventos.
     */
    Camera & camera;

    /**
     * @brief Bandera que indica si el ratón es el primero en moverse.
     *
     * Se usa para controlar el comportamiento inicial del movimiento del ratón y evitar saltos
     * cuando el ratón aún no se ha movido en la ventana.
     */
    bool first_mouse;

    /**
     * @brief Última posición en el eje X del ratón.
     */
    float last_x;

    /**
     * @brief Última posición en el eje Y del ratón.
     */
    float last_y;

    /**
     * @brief Procesa el movimiento del ratón.
     *
     * Esta función actualiza la posición de la cámara en función del movimiento del ratón.
     * Cambia los ángulos de yaw (rotación alrededor del eje vertical) y pitch (rotación alrededor
     * del eje horizontal) en la cámara.
     *
     * @param event El evento de SDL que contiene la información del movimiento del ratón.
     */
    void process_mouse_motion(const SDL_Event & event);

    /**
     * @brief Procesa la entrada del teclado.
     *
     * Esta función actualiza la posición y orientación de la cámara basándose en las teclas
     * presionadas. Se encarga de mover la cámara en distintas direcciones (adelante, atrás, izquierda, derecha)
     * y de ajustar el zoom y la sensibilidad del ratón.
     *
     * @param keystate El estado actual de las teclas presionadas.
     * @param delta_time El tiempo transcurrido entre el fotograma actual y el anterior, utilizado
     *                   para que el movimiento de la cámara sea independiente de la velocidad de fotogramas.
     */
    void process_keyboard(const Uint8 * keystate, float delta_time);
};
