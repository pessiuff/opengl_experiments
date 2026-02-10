#include "gfx/texture.hpp"

#include <stb/image.h>

using namespace opengl_experiments;

bool Texture::initFromFile(const char* fileName, TextureFilter filter) {
    stbi_set_flip_vertically_on_load(true);
    
    int imageWidth, imageHeight, imageChannels;
    unsigned char* imageData = stbi_load(fileName, &imageWidth, &imageHeight, &imageChannels, 3);
    if (imageData == nullptr) {
        return false;
    }

    glGenTextures(1, &m_handle);
    if (m_handle == 0) {
        stbi_image_free(imageData);
        return false;
    }

    glBindTexture(GL_TEXTURE_2D, m_handle);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter == TextureFilter::NEAREST ? GL_NEAREST_MIPMAP_NEAREST : GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter == TextureFilter::NEAREST ? GL_NEAREST : GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imageData);

    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(imageData);

    return true;
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, m_handle);
}

void Texture::destroy() {
    if (m_handle == 0) {
        return;
    }

    glDeleteTextures(1, &m_handle);
    m_handle = 0;
}