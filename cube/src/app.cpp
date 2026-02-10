#include "app.hpp"

#include <shared/core/constants.hpp>
#include <glad/gl.h>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

using namespace opengl_experiments;

constexpr float k_cubeVertices[] = {
    // Position (3) - TexCoord (2)

    // Front Face (z = 0.5)
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // Bottom left
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // Top left
     0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // Bottom right
     0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // Top right

    // Back Face (z = -0.5)
     0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom left (from back view)
     0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // Top left
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // Bottom right
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // Top right

    // Left Face (x = -0.5)
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom left
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // Top left
    -0.5f, -0.5f,  0.5f,  1.0f, 0.0f, // Bottom right
    -0.5f,  0.5f,  0.5f,  1.0f, 1.0f, // Top right

    // Right Face (x = 0.5)
     0.5f, -0.5f,  0.5f,  0.0f, 0.0f, // Bottom left
     0.5f,  0.5f,  0.5f,  0.0f, 1.0f, // Top left
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // Bottom right
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // Top right
     
    // Top Face (y = 0.5)
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, // Bottom left
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, // Top left
     0.5f,  0.5f,  0.5f,  1.0f, 0.0f, // Bottom right
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f, // Top right

    // Bottom Face (y = -0.5)
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, // Bottom left
    -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, // Top left
     0.5f, -0.5f, -0.5f,  1.0f, 0.0f, // Bottom right
     0.5f, -0.5f,  0.5f,  1.0f, 1.0f, // Top right
};

constexpr unsigned int k_cubeIndices[] = {
    // Front Face
    1, 0, 2,
    2, 3, 1,

    // Back Face
    5, 4, 6,
    6, 7, 5,

    // Left Face
    9, 8, 10,
    10, 11, 9,

    // Right Face
    13, 12, 14,
    14, 15, 13,

    // Top Face
    17, 16, 18,
    18, 19, 17,

    // Bottom Face
    21, 20, 22,
    22, 23, 21
};

CubeApp::CubeApp() : App({512, 512, "Texture", true}) {

}

bool CubeApp::init() {
    glfwSetFramebufferSizeCallback(m_pWindow, [](GLFWwindow*, int framebufferWidth, int framebufferHeight) {
        glViewport(0, 0, framebufferWidth, framebufferHeight);
    });

    if (!m_shader.initFromSource(k_positionTexCoordMVPShader, k_textureFragmentShader)) {
        std::cout << "Couldn't initialize the shader program!\n";
        return false;
    }

    m_shader.use();

    glm::mat4 view = glm::mat4(1.0f);
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));

    glm::mat4 projection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 100.0f);

    m_shader.setUniformMat4("view", view);
    m_shader.setUniformMat4("projection", projection);

    if (!m_texture.initFromFile("images/soap.png", TextureFilter::LINEAR)) {
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(k_cubeVertices), &k_cubeVertices, GL_STATIC_DRAW);

    glGenBuffers(1, &m_eboHandle);
    if (m_eboHandle == 0) {
        std::cout << "Couldn't create the element buffer object!\n";
        return false;
    }

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboHandle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(k_cubeIndices), &k_cubeIndices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(0));
    glEnableVertexAttribArray(0);

    // TexCoord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    return true;
}

void CubeApp::update(double deltaTime) {
    constexpr float rotationSpeed = 90.0f; // deg/sec
    static float rotation = deltaTime * rotationSpeed;

    glm::mat4 modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));

    m_shader.setUniformMat4("model", modelMatrix);

    rotation += deltaTime * rotationSpeed;
}

void CubeApp::draw() {
    m_shader.use();
    m_texture.bind();
    glBindVertexArray(m_vaoHandle);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void CubeApp::deinit() {
    glDeleteBuffers(1, &m_eboHandle);
    glDeleteBuffers(1, &m_vboHandle);
    glDeleteVertexArrays(1, &m_vaoHandle);
    m_texture.destroy();
    m_shader.destroy();
}
