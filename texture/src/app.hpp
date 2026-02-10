#pragma once

#include <shared/core/app.hpp>
#include <shared/gfx/shader_program.hpp>
#include <shared/gfx/texture.hpp>

namespace opengl_experiments {
    class TextureApp : public App {
    public:
        TextureApp();

        virtual bool init();
        virtual void update(double deltaTime);
        virtual void draw();
        virtual void deinit();

    private:
        ShaderProgram m_shader {};
        Texture m_texture {};
        GLuint m_vaoHandle = 0;
        GLuint m_vboHandle = 0;
        GLuint m_eboHandle = 0;
    };
}