#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GLFW/glfw3.h>

using namespace glm;

#ifndef CAMERA_H
#define CAMERA_H

class Camera
{
    public:

        vec3 CameraPosition;
        vec3 CameraDirection;
        float FOV;
        GLFWwindow* Window;

        Camera(vec3 cameraPostion, vec3 cameraDirection, float fov, GLFWwindow* window);


        vec3 GetCameraUpVec();
        vec3 GetCameraRightVec();
        mat4 GetCameraView();
        mat4 GetCameraProjection();

        vec2 lastMousePos;
        void MouseInput();


        ~Camera();
};


#endif // MESH_H
