
#include "test_util.h"

class TestWindow:public TestUtil
{
public:

    void OnResize(int width, int height)override
    {
        glViewport(0, 0, width, height);
    }

    void _processInput(GLFWwindow *window)override
    {
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }
};

TEST_F(TestWindow, test_display1)
{
    auto fn=[&](int frame)
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    };

    PlayWindow(fn,120);
}