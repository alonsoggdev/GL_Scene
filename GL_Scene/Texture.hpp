//
//  Texture.hpp
//  GL_Scene
//
//  Created by Alonso García on 24/12/24.
//

#include <string>
#include <glad.h>

namespace udit
{
    enum class Texture_Type
    {
        COLOR,
        HEIGHT
    };

    class Texture
    {
    private:
        bool loaded = false;
        Texture_Type m_type;
    public:
        Texture(const std::string & path, GLenum texture_unit, Texture_Type type = Texture_Type::COLOR);
        ~Texture();
        
        void bind()     const;
        void unbind()   const;
        
        GLuint texture_id;
        GLenum texture_unit;
        std::string file_path;
        
        void load_texture();
        void set_type(Texture_Type type) { m_type = type; }
        bool is_loaded() { return loaded; }
    };
}

