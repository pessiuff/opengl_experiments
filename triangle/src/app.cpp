#include "app.hpp"

#include <shared/core/constants.hpp>
#include <iostream>

using namespace opengl_experiments;

constexpr float k_triangleVertices[] = {
    // Position (3) - Color (3)
    -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,
    0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f,
};

TriangleApp::TriangleApp() : App({512, 512, "Triangle", true}) {

}

bool TriangleApp::init() {
    glfwSetFramebufferSizeCallback(m_pWindow, [](GLFWwindow*, int framebufferWidth, int framebufferHeight) {
        glViewport(0, 0, framebufferWidth, framebufferHeight);
    });

    if (!m_triangleShader.initFromSource(k_positionColorVertexShader, k_solidColorFragmentShader)) {
        std::cout << "Couldn't initialize the shader program!\n";
        return false;
    }

    m_triangleShader.use();
    
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(k_triangleVertices), &k_triangleVertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    return true;
}

void TriangleApp::update() {
    
}

void TriangleApp::draw() {
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void TriangleApp::deinit() {
    m_triangleShader.destroy();
}
