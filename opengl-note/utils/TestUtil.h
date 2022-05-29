#pragma once

#include <gtest/gtest.h>
#include <GLFW/glfw3.h>
#include "camera/camera.h"
#include <functional>

class TestUtil : public testing::Test
{
public:
    static void SetUpTestCase();

    static void TearDownTestCase();

    void SetUp()override;

    void TearDown()override;

    using renderFn=std::function<void(int)>;
    void PlayWindow( renderFn cb,int maxCycle = 0);

protected:

    virtual void _processInput(GLFWwindow*);

    Camera m_camera;

    GLFWwindow* m_window=nullptr;

    // timing
    float deltaTime = 0.0f;	// time between current frame and last frame
    float lastFrame = 0.0f;

};

class GlobalTest:public testing::Environment
{
public:
    void SetUp() override;

    void TearDown()override;
};

