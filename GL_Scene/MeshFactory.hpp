//
//  MeshFactory.hpp
//  GL_Scene
//
//  Created by Alonso García on 26/12/24.
//

#include "Mesh.hpp"
#include "Skybox.hpp"

using udit::MeshType;

class MeshFactory
{
public:
    static std::shared_ptr < udit::Mesh > make_mesh(MeshType type = MeshType::MESH, const std::string & path = "");
};
