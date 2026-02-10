#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace opengl_experiments {
    struct AppParameters {
        int window_width;
        int window_height;
        const char* window_title;
        bool window_resizable;
    };

    class App {
    public:
        App(const AppParameters& params);
        virtual ~App() = default;

        void run();

        virtual bool init() = 0;
        virtual void update() = 0;
        virtual void draw() = 0;
        virtual void deinit() = 0;

    protected:
        AppParameters m_parameters;
        GLFWwindow* m_pWindow = nullptr;
    };
}