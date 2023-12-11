#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Camera.h"
#include "Helper.h"
#include "Mesh.h"
#include "Text.h"



int main()
{
    // setup opengl and craete a window
    if (!glfwInit())
    {
        std::cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Moving Triangle", nullptr, nullptr);
    if (!window)
    {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    // tell opengl to use our new window
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD\n";
        glfwTerminate();
        return -1;
    }


    

    Camera* camera = new Camera(vec3(0, 0, 3), vec3(0, 0, -1), 45.0f, window);

    // create a triangle mesh
    Mesh* mesh = new Mesh(window, camera);

    Mesh* mesh1 = new Mesh(window, camera);
    mesh1->Position = vec3(5, 0, 0);

    Text* text = new Text("H", window);

    float frameTime = 0;
    float prevTime = 0;
    while (!glfwWindowShouldClose(window))
    {
        // Get the time
        frameTime = glfwGetTime() - prevTime;
        prevTime = glfwGetTime();

        printf("%f\n", 1/frameTime);

        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);

        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            camera->CameraPosition += camera->GetCameraRightVec() * -5.0f * frameTime;
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            camera->CameraPosition += camera->GetCameraRightVec() * 5.0f * frameTime;
        }

        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            camera->CameraPosition += camera->CameraDirection * -5.0f * frameTime;
        }

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            camera->CameraPosition += camera->CameraDirection * 5.0f * frameTime;
        }

        camera->MouseInput();

        glClearColor(0.5f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        mesh1->Render();

        mesh->Render();

        text->Render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }



    glfwTerminate();

    return 0;
}