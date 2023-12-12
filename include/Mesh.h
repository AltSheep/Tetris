#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"

#ifndef MESH_H
#define MESH_H

class Mesh
{


private:

    GLuint VertexShader;
    GLuint FragmentShader;
    GLuint ShaderProgram;

    GLuint VBO, VAO;

    GLFWwindow* Window;
    Camera* CameraView;



public:

    vec3 Position;
    vec3 Direction;

    const char* vertexShaderSource =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec3 aColor;\n"
        "uniform mat4 mvp;\n"
        "out vec3 ourColor;\n"
        "void main()\n"
        "{\n"
        "    gl_Position = mvp * vec4(aPos, 1.0);\n"
        "    ourColor = aColor;\n"
        "}\n";

    const char* fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec3 ourColor;\n"
        "void main()\n"
        "{\n"
        "    FragColor = vec4(ourColor, 1.0f);\n"
        "}\n";

    void Render();

    Mesh(GLFWwindow* window, Camera* camera);
    ~Mesh();
};

#endif // MESH_H