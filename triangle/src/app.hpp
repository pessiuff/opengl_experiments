#pragma once

#include <shared/core/app.hpp>
#include <shared/gfx/shader_program.hpp>
#include <glad/gl.h>

namespace opengl_experiments {
    class TriangleApp : public App {
    public:
        TriangleApp();

        virtual bool init();
        virtual void update();
        virtual void draw();
        virtual void deinit();
    
    private:
        ShaderProgram m_triangleShader;
        GLuint m_vaoHandle = 0;
        GLuint m_vboHandle = 0;
    };
}