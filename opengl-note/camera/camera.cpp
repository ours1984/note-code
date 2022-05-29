#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include "camera.h"
#include <vector>

Camera* Camera::s_currentCamera=nullptr;
// constructor with vectors
Camera::Camera()
{
    updateCameraVectors();
}

// returns the view matrix calculated using Euler Angles and the LookAt Matrix
glm::mat4 Camera::GetViewMatrix()const
{
    return glm::lookAt(Position, Position + Front, Up);
}

void Camera::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);

    if (s_currentCamera)
    {
        s_currentCamera->m_left=-width/2.0;
        s_currentCamera->m_right=width/2.0;
        s_currentCamera->m_bottom=-height/2.0;
        s_currentCamera->m_top=-height/2.0;
    }
}


void Camera::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (s_currentCamera)
    {
        if (action == GLFW_PRESS)
            s_currentCamera->button[button]=true;
        else if (action == GLFW_RELEASE)
            s_currentCamera->button[button]=false;       
    }
}

void Camera::mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    static bool firstMouse = false;
    static float lastX=0,lastY=0;

    if (s_currentCamera)
    {
        float xpos = static_cast<float>(xposIn);
        float ypos = static_cast<float>(yposIn);

        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

        lastX = xpos;
        lastY = ypos;

        s_currentCamera->ProcessMouseMovement(xoffset, yoffset);
    }
}

void Camera::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if (s_currentCamera)
    {
        s_currentCamera->ProcessMouseScroll(static_cast<float>(yoffset));
    }
}

void Camera::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (s_currentCamera)
    {
        if(action == GLFW_PRESS)
            s_currentCamera->keys[key] = true;
        else if(action == GLFW_RELEASE)
            s_currentCamera->keys[key] = false;
    }
}

// returns the view matrix calculated using Euler Angles and the LookAt Matrix
glm::mat4 Camera::GetProjectionMatrix()const
{
    return m_perspective?
        glm::perspective(
            glm::radians(Zoom)
            , (m_right-m_left)/ (m_top-m_bottom)
            , m_near, m_far):
        glm::ortho(
            m_right,m_left
            ,m_top,m_bottom
            , m_near, m_far)
        ;
}

// processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Camera::ProcessKeyboard(float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    bool update=false;
    if (keys[GLFW_KEY_W])
    {
        Position += glm::vec3(Front.x,0,Front.z) * velocity;
        update=true;
    }
    if (keys[GLFW_KEY_S])
    {
        Position -= glm::vec3(Front.x,0,Front.z) * velocity;
        update=true;
    } 
    if (keys[GLFW_KEY_A])
    {
        Position -= Right * velocity;
        update=true;
    }
    if (keys[GLFW_KEY_D])
    {
        Position += Right * velocity;
        update=true;
    }
    if (keys[GLFW_KEY_SPACE])
    {
        Yaw = 0;
        Pitch = 0;
        Zoom = 45;
        Position = glm::vec3(0.0f, 0.0f, 3.0f);
        update=true;
    }
    
    if (update)
    {
        // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }
    if (button[GLFW_MOUSE_BUTTON_RIGHT]||button[GLFW_MOUSE_BUTTON_MIDDLE])
    {
        // if (!m_basicShader)
        //     m_basicShader = new Shader("driver/util/inout.vs", "driver/util/inout.fs");

        // m_basicShader->use();
        // m_basicShader->setVec3("cpos",Position+Front*50.0f);
        // m_basicShader->setMat4("view",GetViewMatrix());
        // m_basicShader->setMat4("projection",GetProjectionMatrix());
        // glEnable(GL_POINT_SPRITE_ARB);
        // glPointSize(40);
        // glDrawArrays(GL_POINTS,0,1);
    }
}

// processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera::ProcessMouseMovement(float xoffset, float yoffset, bool constrainPitch)
{
    if (button[GLFW_MOUSE_BUTTON_RIGHT])
    {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw   -= xoffset;
        Pitch += yoffset;

        // make sure that when pitch is out of bounds, screen doesn't get flipped
        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }
        updateCameraVectors();
    }
    else if (button[GLFW_MOUSE_BUTTON_MIDDLE])
    {
        float xvelocity = MovementSpeed * xoffset *0.01f;
        Position -= Right * xvelocity;

        float yvelocity = MovementSpeed * yoffset*0.01f;
        Position -= Up * yvelocity;

        // update Front, Right and Up Vectors using the updated Euler angles
        updateCameraVectors();
    }

}

// processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void Camera::ProcessMouseScroll(float yoffset)
{
    Zoom -= (float)yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 85.0f)
        Zoom = 85.0f; 
}

void Camera::attachCurrentCamera(Camera* ca)
{
    s_currentCamera=ca;    
}

// calculates the front vector from the Camera's (updated) Euler Angles
void Camera::updateCameraVectors()
{
    Front.x = -cos(glm::radians(Pitch))*sin(glm::radians(Yaw));
    Front.y = sin(glm::radians(Pitch));
    Front.z = -cos(glm::radians(Pitch))*cos(glm::radians(Yaw));
    Front = glm::normalize(Front);

    // also re-calculate the Right and Up vector
    Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Up    = glm::normalize(glm::cross(Right, Front));
}