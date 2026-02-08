#include "core/app.hpp"

#include <glad/gl.h>

using namespace opengl_experiments;

App::App(const AppParameters& params) : m_parameters(params) {

}

void App::run() {
    glfwInit();

    glfwWindowHint(GLFW_RESIZABLE, m_parameters.window_resizable ? GLFW_TRUE : GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);

    m_pWindow = glfwCreateWindow(m_parameters.window_width, m_parameters.window_height, m_parameters.window_title, nullptr, nullptr);
    if (!m_pWindow) {
        return;
    }

    glfwMakeContextCurrent(m_pWindow);
    gladLoadGL(static_cast<GLADloadfunc>(glfwGetProcAddress));

    if (!init()) {
        return;
    }

    while (!glfwWindowShouldClose(m_pWindow)) {
        glfwPollEvents();

        update();

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        draw();

        glfwSwapBuffers(m_pWindow);
    }

    deinit();

    glfwTerminate();
}