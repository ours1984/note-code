#pragma once

#include <gtest/gtest.h>
#include <GLFW/glfw3.h>

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

    virtual void OnResize(int width,int height);

protected:

    virtual void _processInput(GLFWwindow*);

    virtual void _beforeRender();

    virtual void _afterRender();

};

class GlobalTest:public testing::Environment
{
public:
    void SetUp() override;

    void TearDown()override;
};

