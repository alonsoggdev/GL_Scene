//
//  Texture.cpp
//  GL_Scene
//
//  Created by Alonso García on 24/12/24.
//

#include "Texture.hpp"
#include "SOIL2.h"
#include <iostream>

using udit::Texture;

Texture::Texture(const std::string & path, GLenum texture_unit, Texture_Type type)
    : file_path(path), texture_unit(texture_unit), m_type(type)
{
    glGenTextures(1, &texture_id);
    bind();
    
    std::cout << "Path: " << path << std::endl;
    
    load_texture();
    
    if (m_type == Texture_Type::HEIGHT)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }
    else
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    unbind();
}

Texture::~Texture()
{
    glDeleteTextures(1, &texture_id);
}

void Texture::bind() const
{
    // std::cout << "Texture unit: " << texture_unit << std::endl;
    glActiveTexture(texture_unit);
    glBindTexture(GL_TEXTURE_2D, texture_id);
}

void Texture::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::load_texture()
{
    std::cout << "Loading texture from: " << file_path << std::endl;
    int width, height, channels;
    unsigned char* image_data = SOIL_load_image(file_path.c_str(), &width, &height, &channels, SOIL_LOAD_AUTO);
    
    if (image_data)
    {
        GLenum format = GL_RGB;
        
        if (channels == 4)
        {
            format = GL_RGBA;
        }
        else if (channels == 1)
        {
            format = GL_RED;
        }
        
        if (m_type == Texture_Type::COLOR)
        {
            glTexImage2D(GL_TEXTURE, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, image_data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else if (m_type == Texture_Type::HEIGHT)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_R16F, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, image_data);
        }
        
        SOIL_free_image_data(image_data);
        loaded = true;
    }
    else
    {
        std::cerr << "Error cargando la textura: " << file_path << std::endl;
    }
}
