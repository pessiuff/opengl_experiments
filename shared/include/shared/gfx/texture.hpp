#pragma once

#include <glad/gl.h>

namespace opengl_experiments {
    enum class TextureFilter {
        NEAREST,
        LINEAR
    };

    class Texture {
    public:
        bool initFromFile(const char* fileName, TextureFilter filter);
        void bind();
        void destroy();

    private:
        GLuint m_handle = 0;
    };
};