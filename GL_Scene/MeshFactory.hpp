//
//  MeshFactory.hpp
//  GL_Scene
//
//  Created by Alonso García on 26/12/24.
//

#include "Mesh.hpp"

class MeshFactory
{
public:
    static std::unique_ptr < udit::Mesh > make_mesh(const std::string & path);
};
