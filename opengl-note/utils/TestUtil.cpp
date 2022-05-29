#include <glad/glad.h>
#include "TestUtil.h"
#include <iostream>
#include <map>

using namespace std;

/*****/
void TestUtil::SetUpTestCase()
{

}

void TestUtil::TearDownTestCase()
{

}

/*****/
void TestUtil::SetUp() // TEST跑之前会执行SetUp
{
    m_window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (m_window == NULL)
    {
        glfwTerminate();
        throw "Failed to create GLFW window;";
    }
    cout << "glfwCreateWindow" << endl;

    glfwMakeContextCurrent(m_window);
    glfwSetFramebufferSizeCallback(m_window, Camera::framebuffer_size_callback);
    glfwSetCursorPosCallback(m_window, Camera::mouse_callback);
    glfwSetScrollCallback(m_window, Camera::scroll_callback);
    glfwSetKeyCallback(m_window,Camera::key_callback);
    glfwSetMouseButtonCallback(m_window,Camera::mouse_button_callback);

    // tell GLFW to capture our mouse
    //glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    m_camera.attachCurrentCamera(&m_camera);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGL())
    {
        cout << "failed gladLoadGL" << endl;
        throw "Failed to gladLoadGL";
    }
}

void TestUtil::TearDown() // TEST跑完之后会执行TearDown
{
    m_camera.attachCurrentCamera(nullptr);
    glfwDestroyWindow(m_window);
}

void TestUtil::PlayWindow(renderFn cb,int maxCycle)
{   
    int i=0;
    while(!glfwWindowShouldClose(m_window)&&(maxCycle<=0 || i++ <maxCycle))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
        glEnable(GL_DEPTH_TEST);
        
        _processInput(m_window);
        cb(i);
        m_camera.ProcessKeyboard(deltaTime);

        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }
}

/*****/
void TestUtil::_processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

}

/*****/
void GlobalTest::SetUp()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

void GlobalTest::TearDown()
{
    glfwTerminate();
}

