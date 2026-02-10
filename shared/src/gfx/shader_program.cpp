#include "gfx/shader_program.hpp"

#include <glad/gl.h>
#include <glm/gtc/type_ptr.hpp>

using namespace opengl_experiments;

bool ShaderProgram::initFromSource(const char* vertexSource, const char* fragmentSource) {
    if (m_handle != 0) {
        glDeleteProgram(m_handle);
        m_handle = 0;
    }

    GLuint vertexHandle = glCreateShader(GL_VERTEX_SHADER);
    if (vertexHandle == 0) {
        return false;
    }

    GLuint fragmentHandle = glCreateShader(GL_FRAGMENT_SHADER);
    if (fragmentHandle == 0) {
        glDeleteShader(vertexHandle);
        return false;
    }

    glShaderSource(vertexHandle, 1, &vertexSource, nullptr);
    glCompileShader(vertexHandle);
    
    GLint vertexCompileStatus;
    glGetShaderiv(vertexHandle, GL_COMPILE_STATUS, &vertexCompileStatus);
    if (vertexCompileStatus != GL_TRUE) {
        glDeleteShader(vertexHandle);
        glDeleteShader(fragmentHandle);
        return false;
    }

    glShaderSource(fragmentHandle, 1, &fragmentSource, nullptr);
    glCompileShader(fragmentHandle);
    
    GLint fragmentCompileStatus;
    glGetShaderiv(fragmentHandle, GL_COMPILE_STATUS, &fragmentCompileStatus);
    if (fragmentCompileStatus != GL_TRUE) {
        glDeleteShader(vertexHandle);
        glDeleteShader(fragmentHandle);
        return false;
    }

    m_handle = glCreateProgram();
    if (m_handle == 0) {
        glDeleteShader(vertexHandle);
        glDeleteShader(fragmentHandle);
        return false;
    }

    glAttachShader(m_handle, vertexHandle);
    glAttachShader(m_handle, fragmentHandle);

    glLinkProgram(m_handle);

    GLint programLinkStatus;
    glGetProgramiv(m_handle, GL_LINK_STATUS, &programLinkStatus);
    if (programLinkStatus != GL_TRUE) {
        glDeleteShader(vertexHandle);
        glDeleteShader(fragmentHandle);
        glDeleteProgram(m_handle);
        m_handle = 0;
        return false;
    }

    glDetachShader(m_handle, vertexHandle);
    glDetachShader(m_handle, fragmentHandle);
    
    glDeleteShader(vertexHandle);
    glDeleteShader(fragmentHandle);

    return true;
}

void ShaderProgram::use() {
    glUseProgram(m_handle);
}

void ShaderProgram::destroy() {
    if (m_handle == 0) {
        return;
    }
    
    glDeleteProgram(m_handle);
    m_handle = 0;
}

void ShaderProgram::setUniformMat4(const char* uniformName, const glm::mat4& value) {
    if (m_handle == 0) {
        return;
    }

    glUniformMatrix4fv(glGetUniformLocation(m_handle, uniformName), 1, GL_FALSE, glm::value_ptr(value));
}