#pragma once

#include <glm/glm.hpp>

namespace opengl_experiments {
    class ShaderProgram {
    public:
        bool initFromSource(const char* vertexSource, const char* fragmentSource);
        void use();
        void destroy();

        void setUniformMat4(const char* uniformName, const glm::mat4& value);

    private:
        unsigned int m_handle = 0;
    };
}