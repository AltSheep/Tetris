#include "Camera.h"
#include "Helper.h"

using namespace glm;

Camera::Camera(vec3 cameraPosition, vec3 cameraDirection, float fov, GLFWwindow* window)
{
    CameraPosition = cameraPosition;
    CameraDirection = cameraDirection;
    FOV = fov;
    Window = window;

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

vec3 Camera::GetCameraUpVec()
{
    // get the right vector poiting right of the camera
    vec3 cameraRightVec = glm::cross(CameraDirection, Helper::WORLD_UP_VECTOR);

    // get the up vector by cross product camera look direction with right vector
    return glm::cross(cameraRightVec, CameraDirection);
}

mat4 Camera::GetCameraView()
{
    return glm::lookAt(CameraPosition, CameraPosition + CameraDirection, GetCameraUpVec());
}

mat4 Camera::GetCameraProjection()
{
    // get the resolution of the window
    int width, height;
    glfwGetWindowSize(Window, &width, &height);

    return glm::perspective(glm::radians(FOV), (float)width / (float)height, 0.1f, 100.0f);
}

void Camera::MouseInput()
{
    double mouseX, mouseY;
    glfwGetCursorPos(Window, &mouseX, &mouseY);

     float sensitivity = 0.05f;
    // mouseX *= sensitivity;
    // mouseY *= sensitivity;

    float yawMovement = (lastMousePos.x - mouseX) * sensitivity;

    lastMousePos.x = mouseX;



    printf("%f\n", yawMovement);

    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(yawMovement), glm::vec3(0.0f, 1.0f, 0.0f));
    CameraDirection = rotationMatrix * glm::vec4(CameraDirection, 0.0f);


    // Calculate new front vector
    //glm::vec3 front;
    //front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    //front.y = sin(glm::radians(pitch));
    //front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    // Update camera direction
    //CameraDirection = glm::normalize(front);
}

Camera::~Camera()
{
}
