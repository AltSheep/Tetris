#include <string>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>

#include "glad/glad.h"

using namespace std;

struct CharMap
{
    int x, y; // lookup coordiante
    float texWidth, texHeight;
};


class Text
{
private:

    string DisplayText;

    GLFWwindow* Window;

    GLuint TileSetTexture;

    map<char, CharMap> CharTileMap;

    GLuint VBO, VAO;

    GLuint VertexShader;
    GLuint FragmentShader;
    GLuint ShaderProgram;

    const char* vertexShaderSource =
        "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "layout (location = 1) in vec2 aTexCord;\n"
        "uniform mat4 mvp;\n"
        "out vec2 TexCoord; // Output variable for texture coordinates\n"
        "void main()\n"
        "{\n"
        "    gl_Position = mvp * vec4(aPos, 1.0);\n"
        "    TexCoord = aTexCord;\n"
        "}\n";

    const char* fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "in vec2 TexCoord;\n"
        "uniform sampler2D textureSampler;"
        "void main()\n"
        "{\n"
        "    FragColor = texture(textureSampler, TexCoord);\n"
        "}\n";

public:

    Text(string text, GLFWwindow* window);

    void Render();

    ~Text();

};

