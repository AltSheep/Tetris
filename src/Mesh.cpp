#include "Mesh.h"
#include "Camera.h"
#include "Helper.h"


// constrictor called when you make a new mesh
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
    // Vertices for a regular octahedron
    // Top pyramid
    0.0f, 1.0f, 0.0f,     1.0f, 0.0f, 0.0f, // Top vertex
    1.0f, 0.0f, 0.0f,     0.0f, 1.0f, 0.0f, // Bottom right vertex
    0.0f, 0.0f, 1.0f,     0.0f, 0.0f, 1.0f, // Bottom front vertex

    // Right pyramid
    0.0f, 1.0f, 0.0f,     1.0f, 0.0f, 0.0f, // Top vertex
    0.0f, 0.0f, 1.0f,     0.0f, 0.0f, 1.0f, // Bottom front vertex
    -1.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f, // Bottom left vertex

    // Front pyramid
    0.0f, 1.0f, 0.0f,     1.0f, 0.0f, 0.0f, // Top vertex
    -1.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f, // Bottom left vertex
    0.0f, 0.0f, -1.0f,    0.0f, 0.0f, 1.0f, // Bottom back vertex

    // Left pyramid
    0.0f, 1.0f, 0.0f,     1.0f, 0.0f, 0.0f, // Top vertex
    0.0f, 0.0f, -1.0f,    0.0f, 0.0f, 1.0f, // Bottom back vertex
    1.0f, 0.0f, 0.0f,     0.0f, 1.0f, 0.0f, // Bottom right vertex

    0.0f, -1.0f, 0.0f,     1.0f, 0.0f, 0.0f, // Top vertex
    1.0f, 0.0f, 0.0f,     0.0f, 1.0f, 0.0f, // Bottom right vertex
    0.0f, 0.0f, 1.0f,     0.0f, 0.0f, 1.0f, // Bottom front vertex

    // Right pyramid
    0.0f, -1.0f, 0.0f,     1.0f, 0.0f, 0.0f, // Top vertex
    0.0f, 0.0f, 1.0f,     0.0f, 0.0f, 1.0f, // Bottom front vertex
    -1.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f, // Bottom left vertex

    // Front pyramid
    0.0f, -1.0f, 0.0f,     1.0f, 0.0f, 0.0f, // Top vertex
    -1.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f, // Bottom left vertex
    0.0f, 0.0f, -1.0f,    0.0f, 0.0f, 1.0f, // Bottom back vertex

    // Left pyramid
    0.0f, -1.0f, 0.0f,     1.0f, 0.0f, 0.0f, // Top vertex
    0.0f, 0.0f, -1.0f,    0.0f, 0.0f, 1.0f, // Bottom back vertex
    1.0f, 0.0f, 0.0f,     0.0f, 1.0f, 0.0f, // Bottom right vertex
    };

    // move the verts onto the graphics card
    glGenVertexArrays(1, &VAO);

    // create object on GPU to hold verticies array 
    glGenBuffers(1, &VBO);

    // tell GPU we want to modifyt our rainbow traingle object
    glBindVertexArray(VAO);

    // copy our vertices over to GPU
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // tell teh gpu which verts are psotion
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // tell teh GPU which verts are the color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // telll GPU we are done transfering
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glEnable(GL_DEPTH_TEST);

}

void Mesh::Render()
{
    // rotate the mesh
    //float rotateAmmount = glm::radians(glfwGetTime());
    //glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotateAmmount), vec3(0.0f, 1.0f, 0.0f));
    //Direction = rotationMatrix * vec4(Direction, 0.0f);
    
    
    //Helper::printVector(Direction);


    // create model to apply the meshes postion and rotation
    // glm::mat4 model = glm::mat4(1.0f);
    // model = glm::lookAt(Position, Position + Direction, Helper::WORLD_UP_VECTOR);
    // model = glm::translate(glm::mat4(1.0f), Position) * model;
    
    // //Helper::printVector(CameraView->CameraPosition);
    // //Helper::printMatrix(model);

    // glUseProgram(ShaderProgram);
    // glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "model"), 1, GL_FALSE, glm::value_ptr(model));
    // glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(CameraView->GetCameraView()));
    // glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(CameraView->GetCameraProjection()));




    glm::mat4 modelMatrix = glm::lookAt(Position, Position + Direction, Helper::WORLD_UP_VECTOR);
    modelMatrix = glm::translate(glm::mat4(1.0f), Position) * modelMatrix;

    glm::mat4 viewMatrix = CameraView->GetCameraView();
    glm::mat4 projectionMatrix = CameraView->GetCameraProjection();

     glm::mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;
    


    Helper::printVector(vec3(0, 0, 0));
    Helper::printMatrix(mvp);
    Helper::printVector(mvp * vec4(0, 0, 0, 1));

    

    glUseProgram(ShaderProgram);
    glUniformMatrix4fv(glGetUniformLocation(ShaderProgram, "mvp"), 1, GL_FALSE, glm::value_ptr(mvp));



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
