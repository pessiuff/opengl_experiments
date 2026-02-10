#include "app.hpp"

#include <shared/core/constants.hpp>
#include <glad/gl.h>
#include <iostream>

using namespace opengl_experiments;

constexpr float k_quadVertices[] = {
    // Position (3) - TexCoord (2)
    -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // Bottom left
    -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, // Top left
    0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // Bottom right
    0.5f, 0.5f, 0.0f, 1.0f, 1.0f, // Top right
};

constexpr unsigned int k_quadIndices[] = {
      1, 0, 2, // First triangle
      2, 3, 1 // Second triangle
};

TextureApp::TextureApp() : App({512, 512, "Texture", true}) {

}

bool TextureApp::init() {
    glfwSetFramebufferSizeCallback(m_pWindow, [](GLFWwindow*, int framebufferWidth, int framebufferHeight) {
        glViewport(0, 0, framebufferWidth, framebufferHeight);
    });

    if (!m_shader.initFromSource(k_positionTexCoordVertexShader, k_textureFragmentShader)) {
        std::cout << "Couldn't initialize the shader program!\n";
        return false;
    }

    m_shader.use();

    if (!m_texture.initFromFile("images/pigeon.png", TextureFilter::LINEAR)) {
        std::cout << "Couldn't initialize the texture!\n";
        return false;
    }
    
    m_texture.bind();

    glGenVertexArrays(1, &m_vaoHandle);
    if (m_vaoHandle == 0) {
        std::cout << "Couldn't create the vertex array object!\n";
        return false;
    }

    glBindVertexArray(m_vaoHandle);

    glGenBuffers(1, &m_vboHandle);
    if (m_vboHandle == 0) {
        std::cout << "Couldn't create the vertex buffer object!\n";
        return false;
    }

    glBindBuffer(GL_ARRAY_BUFFER, m_vboHandle);
    glBufferData(GL_ARRAY_BUFFER, sizeof(k_quadVertices), &k_quadVertices, GL_STATIC_DRAW);

    glGenBuffers(1, &m_eboHandle);
    if (m_eboHandle == 0) {
        std::cout << "Couldn't create the element buffer object!\n";
        return false;
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboHandle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(k_quadIndices), &k_quadIndices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);

    // TexCoord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    return true;
}

void TextureApp::update() {
    
}

void TextureApp::draw() {
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void TextureApp::deinit() {
    glDeleteBuffers(1, &m_eboHandle);
    glDeleteBuffers(1, &m_vboHandle);
    glDeleteVertexArrays(1, &m_vaoHandle);
    m_texture.destroy();
    m_shader.destroy();
}
