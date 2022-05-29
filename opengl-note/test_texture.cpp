#include <glad/glad.h>
#include "utils/TestUtil.h"
#include "program/shader.h"
#include "program/texture.h"
#include <cmath>

class TestTexture:public TestUtil
{
public:
    void GenVboIbo()
    {
        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        float vertices[] = {
            // positions          // colors           // texture coords
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
        };


        unsigned int VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        // texture coord attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };
        unsigned int EBO;
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    }

    void GenVboIbo2()
    {
        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        float vertices[] = {
        // positions          // colors           // texture coords (note that we changed them to 2.0f!)
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   2.0f, 2.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   2.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 2.0f  // top left 
        };


        unsigned int VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        // texture coord attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };
        unsigned int EBO;
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    }

protected:
    void _processInput(GLFWwindow* window)override
    {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
    {
        m_mix += 0.001f; // change this value accordingly (might be too slow or too fast based on system hardware)
        if(m_mix >= 1.0f)
            m_mix = 1.0f;
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
    {
        m_mix -= 0.001f; // change this value accordingly (might be too slow or too fast based on system hardware)
        if (m_mix <= 0.0f)
            m_mix = 0.0f;
    }
    }

    float m_mix=0;
};

TEST_F(TestTexture, merge)
{
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    // 1. 绑定VAO
    glBindVertexArray(VAO);
    // 2. 把顶点数组复制到缓冲中供OpenGL使用
    GenVboIbo();
    // 3. 生成纹理
    auto texture1= generateTexture("driver/awesomeface.png");

    // build and compile our shader program
    // ------------------------------------
    Shader ourShader("driver/test_texture/laugh.vs", "driver/test_texture/merge.fs"); // you can name your shader files however you like

    auto fn=[&](int frame)
    {
        ourShader.use();

        ourShader.setTextureUnit("ourTexture", texture1, 0);

        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    };

    PlayWindow(fn,20);

    glDeleteVertexArrays(1, &VAO);
    glDeleteProgram(ourShader.ID);
}

TEST_F(TestTexture, laugh)
{
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    // 1. 绑定VAO
    glBindVertexArray(VAO);
    // 2. 把顶点数组复制到缓冲中供OpenGL使用
    GenVboIbo();
    // 3. 生成纹理
    auto texture1= generateTexture("driver/container.jpg");

    auto texture2= generateTexture("driver/awesomeface.png");

    // build and compile our shader program
    // ------------------------------------
    Shader ourShader("driver/test_texture/laugh.vs", "driver/test_texture/laugh.fs"); // you can name your shader files however you like

    auto fn=[&](int frame)
    {
        ourShader.use();

        ourShader.setTextureUnit("texture1", texture1, 0);

        ourShader.setTextureUnit("texture2", texture2, 1);

        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    };

    PlayWindow(fn,20);

    glDeleteVertexArrays(1, &VAO);
    glDeleteProgram(ourShader.ID);
}

TEST_F(TestTexture, right)
{
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    // 1. 绑定VAO
    glBindVertexArray(VAO);
    // 2. 把顶点数组复制到缓冲中供OpenGL使用
    GenVboIbo();
    // 3. 生成纹理
    auto texture1= generateTexture("driver/container.jpg");

    auto texture2= generateTexture("driver/awesomeface.png");

    // build and compile our shader program
    // ------------------------------------
    Shader ourShader("driver/test_texture/laugh.vs", "driver/test_texture/right.fs"); // you can name your shader files however you like

    auto fn=[&](int frame)
    {
        ourShader.use();

        ourShader.setTextureUnit("texture1", texture1, 0);

        ourShader.setTextureUnit("texture2", texture2, 1);

        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    };

    PlayWindow(fn,20);

    glDeleteVertexArrays(1, &VAO);
    glDeleteProgram(ourShader.ID);
}

TEST_F(TestTexture, wrapping)
{
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    // 1. 绑定VAO
    glBindVertexArray(VAO);
    // 2. 把顶点数组复制到缓冲中供OpenGL使用
    GenVboIbo2();
    // 3. 生成纹理
    auto texture1= generateTexture("driver/container.jpg");
    // note that we set the container wrapping method to GL_CLAMP_TO_EDGE
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); 
    

    auto texture2= generateTexture("driver/awesomeface.png");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	
    // we want to repeat the awesomeface pattern so we kept it at GL_REPEAT

    // build and compile our shader program
    // ------------------------------------
    Shader ourShader("driver/test_texture/laugh.vs", "driver/test_texture/laugh.fs"); // you can name your shader files however you like

    auto fn=[&](int frame)
    {
        ourShader.use();

        ourShader.setTextureUnit("texture1", texture1, 0);

        ourShader.setTextureUnit("texture2", texture2, 1);

        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    };

    PlayWindow(fn,20);

    glDeleteVertexArrays(1, &VAO);
    glDeleteProgram(ourShader.ID);
}

TEST_F(TestTexture, mix)
{
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    // 1. 绑定VAO
    glBindVertexArray(VAO);
    // 2. 把顶点数组复制到缓冲中供OpenGL使用
    GenVboIbo2();
    // 3. 生成纹理
    auto texture1= generateTexture("driver/container.jpg");
    // note that we set the container wrapping method to GL_CLAMP_TO_EDGE
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); 
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); 
    auto texture2= generateTexture("driver/awesomeface.png");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);	
    // we want to repeat the awesomeface pattern so we kept it at GL_REPEAT

    // build and compile our shader program
    // ------------------------------------
    Shader ourShader("driver/test_texture/laugh.vs", "driver/test_texture/mix.fs"); // you can name your shader files however you like

    auto fn=[&](int frame)
    {
        ourShader.use();

        ourShader.setFloat("mixIndex",m_mix+frame/100.0);

        ourShader.setTextureUnit("texture1", texture1, 0);

        ourShader.setTextureUnit("texture2", texture2, 1);

        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    };

    PlayWindow(fn,100);

    glDeleteVertexArrays(1, &VAO);
    glDeleteProgram(ourShader.ID);
}
