#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include "program/shader.h"

// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class Camera
{
public:
    // constructor with vectors
    Camera();

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix()const;
    glm::mat4 GetProjectionMatrix()const;

    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard( float deltaTime);

    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
    void mouse_callback(GLFWwindow* window, double xpos, double ypos);
    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

protected:
    // processes input received from a mouse input system. Expects the offset value in both the x and y direction.
    void _ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch = true);

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void _ProcessMouseScroll(float yoffset);

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void __updateCameraVectors();

    // camera Attributes
    glm::vec3 Position = glm::vec3(0.0f, 0.0f, 3.0f);

    glm::vec3 WorldUp = glm::vec3(0.0f, 1.0f, 0.0f);

    // euler Angles
    float Yaw = 0.0f;
    float Pitch = 0.0f;

    //view matrix
    glm::vec3 Up ;
    glm::vec3 Front;
    glm::vec3 Right;

    //projection matrix
    float Zoom = 45.0f;
    bool m_perspective = true;
    float m_left =-400.0f,m_right = 400.0f;
    float m_bottom= -300.0f,m_top = 300.0f;
    float m_near = 0.1f,m_far = 100;

    // camera options
    float MovementSpeed = 2.5f;
    float MouseSensitivity = 0.1f;
    bool keys[1024]={0};
    bool button[8]={0};
    

    Shader *m_basicShader=nullptr;
};
#endif
