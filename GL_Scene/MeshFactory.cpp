//
//  MeshFactory.cpp
//  GL_Scene
//
//  Created by Alonso García on 26/12/24.
//

#include "MeshFactory.hpp"

std::shared_ptr <udit::Mesh> MeshFactory::make_mesh(const std::string &path)
{
    std::string absolute_path = "/Users/alonsoggdev/UDIT/Asignaturas/Programacion_Grafica/GL_Scene/resources/";
    std::string complete_path = absolute_path + path;
    
    auto mesh = std::make_unique<udit::Mesh>(complete_path);
    return mesh;
}
