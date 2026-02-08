#pragma once

namespace opengl_experiments {
    constexpr char k_positionColorVertexShader[] = R"(
    #version 330 core

    layout (location = 0) in vec3 a_Pos;
    layout (location = 1) in vec3 a_Color;

    out vec3 vertexColor;

    void main() {
        gl_Position = vec4(a_Pos, 1.0f);
        vertexColor = a_Color;
    }
    )";

    constexpr char k_solidColorFragmentShader[] = R"(
    out vec4 fragmentColor;

    in vec3 vertexColor;

    void main() {
        fragmentColor = vec4(vertexColor, 1.0f);
    }
    )";
}