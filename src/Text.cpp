#include "Text.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Text::Text(string text, GLFWwindow* window)
{
    DisplayText = text;

    Window = window;

    glGenTextures(1, &TileSetTexture);
    glBindTexture(GL_TEXTURE_2D, TileSetTexture);

    // Load your texture here (e.g., using SOIL, stb_image, etc.)
    int x, y, channels;
    unsigned char* image = stbi_load("../Assets/Text_Tile_Set.png", &x, &y, &channels, 0);

    char test = image[2];
    if (image == nullptr) 
    {
        printf("FAILED TO LOAD TEXT TILESHEET\n");
    }

    // move texture to GPU
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

    // Set texture parameters (adjust as needed)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_image_free(image);

    glBindTexture(GL_TEXTURE_2D, 0);

    //
    int charWidth = x / 16;
    int charHeight = y / 8;

    // setup hte map
    // loop over all tiles in tile texture
    char character = 0;
    for(int row = 0; row < 16; row++)
    {
        for(int col = 0; col < 8; col++)
        {
            CharMap cm;
            cm.texWidth = charWidth;
            cm.texHeight = charHeight;
            cm.x = col * charWidth;
            cm.y = row * charHeight;

            CharTileMap[character] = cm;

            character++;
        }
    }

    // compile our mesh shaders
    VertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(VertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(VertexShader);

    FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(FragmentShader);

    // combine the shaders to a shader program to execute
    ShaderProgram = glCreateProgram();
    glAttachShader(ShaderProgram, VertexShader);
    glAttachShader(ShaderProgram, FragmentShader);
    glLinkProgram(ShaderProgram);

    // Set up vertex and texture coordinate data for the quad
    float vertices[] = 
    {
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f,
         0.5f, -0.5f, 0.0f,     1.0f, 0.0f,
         0.5f,  0.5f, 0.0f,     1.0f, 1.0f,

        0.5f,  0.5f, 0.0f,     0.0f, 1.0f,
         -0.5f,  0.5f, 0.0f,     1.0f, 1.0f,
        -.5f,  -0.5f, 0.0f,    0.0f, 0.0f,
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Assuming you have a vertex array object (VAO) and vertex buffer object (VBO) set up
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Set up vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // unbind the vbo and vao we are setting up
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Text::Render()
{



    // Loop through characters in your text
    for (const char* c = "H"; *c; c++) 
    {
        CharMap tileSetLookup = CharTileMap[*c];

        // Calculate position and size for the quad
        // ...
        glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 mvp = projection * view * model;


        glUseProgram(ShaderProgram);
        glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "mvp"), 1, GL_FALSE, glm::value_ptr(mvp));

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, TileSetTexture);
        glUniform1i(glGetUniformLocation(ShaderProgram, "textureSampler"), 0);

        // bind the mesh we want to draw then draw it
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

}

Text::~Text()
{
}
