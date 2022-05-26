#include <glad/glad.h>
#include "test_util.h"
#include <iostream>
#include <map>

using namespace std;
static TestUtil* s_testwin = nullptr;
static GLFWwindow* s_windows = nullptr;

static void __defaultFramebufferSizeCallback(GLFWwindow* window,int width, int height)
{
    if (s_testwin)
    {
        s_testwin->OnResize(width,height);
    }
}

/*****/
void TestUtil::SetUpTestCase()
{
    s_windows = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (s_windows == NULL)
    {
        glfwTerminate();
        cout << "Failed to create GLFW window" << endl;
        return;
    }
    cout << "glfwCreateWindow" << endl;

    glfwMakeContextCurrent(s_windows);
    glfwSetFramebufferSizeCallback(s_windows, __defaultFramebufferSizeCallback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "failed gladLoadGLLoader" << endl;
    } 
}

void TestUtil::TearDownTestCase()
{
    glfwDestroyWindow(s_windows);
}

/*****/
void TestUtil::SetUp() // TEST跑之前会执行SetUp
{

}

void TestUtil::TearDown() // TEST跑完之后会执行TearDown
{

}

void TestUtil::PlayWindow(renderFn cb,int maxCycle)
{
    s_windows = glfwGetCurrentContext();
    if (s_windows==nullptr)
    {
        cout << "no glfwGetCurrentContext" << endl;
        return;
    }
    
    s_testwin = this;
    int i=0;
    while(!glfwWindowShouldClose(s_windows)&&(maxCycle<=0 || i++ <maxCycle))
    {
        _beforeRender();

        _processInput(s_windows);

        cb(i);

        _afterRender();
    }
    s_testwin = nullptr;
}

/*****/
void TestUtil::_processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void TestUtil::_beforeRender()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

void TestUtil::_afterRender()
{
    glfwSwapBuffers(s_windows);
    glfwPollEvents();
}

/*****/
void TestUtil::OnResize(int width,int height)
{
    glViewport(0, 0, width, height);
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

