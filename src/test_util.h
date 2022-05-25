#pragma once

#include <gtest/gtest.h>

class TestUtil : public testing::Test
{
public:
    static void SetUpTestCase();

    static void TearDownTestCase();

    virtual void SetUp();

    virtual void TearDown();
};

class GlobalTest:public testing::Environment
{
public:
    void SetUp() override;

    void TearDown()override;
};

