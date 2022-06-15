#include <softrender/glSoft.h>
#include "TestUtil.h"
#include <iostream>
#include <map>
#include "Func2Point.h"

REGISTER_CALLBACK_CLASS(FSCBIND,void(GLFWwindow*,int,int));
REGISTER_CALLBACK_CLASS(MCBIND,void(GLFWwindow*,double,double));
REGISTER_CALLBACK_CLASS(SCBIND,void(GLFWwindow*,double,double));
REGISTER_CALLBACK_CLASS(KCBIND,void(GLFWwindow*,int,int,int,int));
REGISTER_CALLBACK_CLASS(MBCBIND,void(GLFWwindow*,int,int,int));

using namespace std;
static GLFWwindow* m_window=nullptr;

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
    FSCBIND::func = std::bind(&Camera::framebuffer_size_callback, &m_camera
    , std::placeholders::_1, std::placeholders::_2,std::placeholders::_3);
    glfwSetFramebufferSizeCallback(m_window,FSCBIND::callback);

    MCBIND::func = std::bind(&Camera::mouse_callback, &m_camera
        , std::placeholders::_1, std::placeholders::_2,std::placeholders::_3);
    glfwSetCursorPosCallback(m_window,MCBIND::callback);

    SCBIND::func = std::bind(&Camera::scroll_callback, &m_camera
    , std::placeholders::_1, std::placeholders::_2,std::placeholders::_3);
    glfwSetScrollCallback(m_window,SCBIND::callback);

    KCBIND::func = std::bind(&Camera::key_callback, &m_camera
    , std::placeholders::_1, std::placeholders::_2,std::placeholders::_3,std::placeholders::_4,std::placeholders::_5);
    glfwSetKeyCallback(m_window,KCBIND::callback);

    MBCBIND::func = std::bind(&Camera::mouse_button_callback, &m_camera
    , std::placeholders::_1, std::placeholders::_2,std::placeholders::_3,std::placeholders::_4);
    glfwSetMouseButtonCallback(m_window,MBCBIND::callback);
}

void TestUtil::TearDown() // TEST跑完之后会执行TearDown
{

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

    m_window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (m_window == NULL)
    {
        glfwTerminate();
        throw "Failed to create GLFW window;";
    }

    glfwMakeContextCurrent(m_window);

    // tell GLFW to capture our mouse
    //glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!initRender())
    {
        cout << "failed initRender" << endl;
        throw "Failed to initRender";
    }
}

void GlobalTest::TearDown()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

