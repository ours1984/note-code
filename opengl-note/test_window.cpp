
#include "utils/TestUtil.h"

class TestWindow:public TestUtil
{
public:

    void _processInput(GLFWwindow *window)override
    {
        if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
    }
};

TEST_F(TestWindow, windows)
{
    auto fn=[&](int frame)
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
    };

    PlayWindow(fn,10);
}