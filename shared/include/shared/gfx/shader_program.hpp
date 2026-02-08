#pragma once

namespace opengl_experiments {
    class ShaderProgram {
    public:
        bool initFromSource(const char* vertexSource, const char* fragmentSource);
        void use();
        void destroy();

    private:
        unsigned int m_handle = 0;
    };
}