//
//  MeshFactory.cpp
//  GL_Scene
//
//  Created by Alonso García on 26/12/24.
//

#include "MeshFactory.hpp"

std::shared_ptr <udit::Mesh> MeshFactory::make_mesh(MeshType type, const std::string &path)
{
    std::string absolute_path = "/Users/alonsoggdev/UDIT/Asignaturas/Programacion_Grafica/GL_Scene/resources/";
    std::string complete_path = absolute_path + path;
    switch (type)
    {
        case MeshType::TERRAIN:
        case MeshType::BASIC:
            break;
            
        case MeshType::MESH:
            return path.empty() ? std::make_shared<udit::Mesh>()
                                : std::make_shared<udit::Mesh>(complete_path);
        case MeshType::SKYBOX:
            std::vector<std::string> skybox_faces =
            {
                   "skybox_east.jpg", "skybox_west.jpg", "skybox_up.jpg",
                   "skybox_down.jpg", "skybox_north.jpg", "skybox_south.jpg"
            };
            return std::make_shared<udit::Skybox>(100.0f, skybox_faces);
    }
    return nullptr;
    
}
