#include "Mesh.h"
#include "Camera.h"
#include "Helper.h"


Mesh::Mesh(GLFWwindow* window, Camera* camera)
{
    Window = window;
    CameraView = camera;
    Direction = vec3(1, 0, 0);

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

    // add rriangles to our mesh
    float vertices[] = 
    {
        // postion                  // color R, G ,B
        0.0f, 0.0f, 0.0f,         1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,         1.0f, 0.0f, 0.0f,
        1.0f,  0.0f, 0.0f,        1.0f, 0.0f, 0.0f,

        // postion                  // color R, G ,B
        1.0f, 1.0f, 0.0f,         0.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 0.0f,         0.0f, 1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,        0.0f, 1.0f, 0.0f,
        
        1.0f, 0.0f, 0.0f,         0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 0.0f,         0.0f, 0.0f, 1.0f,
        2.0f,  0.0f, 0.0f,        0.0f, 0.0f, 1.0f,

        // postion                  // color R, G ,B
        2.0f, 1.0f, 0.0f,         1.0f, 1.0f, 0.0f,
        2.0f, 0.0f, 0.0f,         1.0f, 1.0f, 0.0f,
        1.0f,  1.0f, 0.0f,        1.0f, 1.0f, 0.0f,

        // postion                  // color R, G ,B
        2.0f, 0.0f, 0.0f,         1.0f, 0.0f, 1.0f,
        2.0f, 1.0f, 0.0f,         1.0f, 0.0f, 1.0f,
        3.0f,  0.0f, 0.0f,        1.0f, 0.0f, 1.0f,

        // postion                  // color R, G ,B
        3.0f, 1.0f, 0.0f,         0.0f, 1.0f, 0.0f,
        3.0f, 0.0f, 0.0f,         0.0f, 1.0f, 0.0f,
        2.0f,  1.0f, 0.0f,        0.0f, 1.0f, 0.0f,
        
        3.0f, 0.0f, 0.0f,         0.0f, 0.0f, 1.0f,
        3.0f, 1.0f, 0.0f,         0.0f, 0.0f, 1.0f,
        4.0f,  0.0f, 0.0f,        0.0f, 0.0f, 1.0f,

        // postion                  // color R, G ,B
        4.0f, 1.0f, 0.0f,         1.0f, 1.0f, 0.0f,
        4.0f, 0.0f, 0.0f,         1.0f, 1.0f, 0.0f,
        3.0f,  1.0f, 0.0f,        1.0f, 1.0f, 0.0f
    };

    // move the verts onto the graphics card
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glEnable(GL_DEPTH_TEST);

}

void Mesh::Render()
{
    // rotate the mesh
    float rotateAmmount = glm::radians(glfwGetTime());
    //glm::mat4 rotationMatrix = glm::rotate(mat4(1.0f), rotateAmmount, vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotateAmmount), vec3(0.0f, 1.0f, 0.0f));
    Direction = rotationMatrix * vec4(Direction, 0.0f);
    //Helper::printVector(Direction);


    // create model to apply the meshes postion and rotation
    glm::mat4 model = glm::mat4(1.0f);

    model = glm::lookAt(Position, Position + Direction, Helper::WORLD_UP_VECTOR);
    model = glm::translate(glm::mat4(1.0f), Position) * model;
    
    //Helper::printVector(CameraView->CameraPosition);
    //Helper::printMatrix(model);

    glUseProgram(ShaderProgram);
    glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(CameraView->GetCameraView()));
    glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(CameraView->GetCameraProjection()));

    // bind the mesh we want to draw then draw it
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 24);
}

Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(ShaderProgram);
}
