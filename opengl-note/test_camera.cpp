#include <glad/glad.h>
#include "utils/TestUtil.h"
#include "program/shader.h"
#include "program/texture.h"
#include <cmath>

class TestMVP:public TestUtil
{
public:
    void Gen6BoxVbo()
    {
        // set up vertex data (and buffer(s)) and configure vertex attributes
        // ------------------------------------------------------------------
        float vertices[] = {
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
            0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
        };

        unsigned int VBO;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // texture coord attribute
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
    }

    void Get1BoxVbo()
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

};

TEST_F(TestMVP, 1box)
{
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    // 1. 绑定VAO
    glBindVertexArray(VAO);
    // 2. 把顶点数组复制到缓冲中供OpenGL使用
    Get1BoxVbo();
    // 3. 生成纹理
    auto texture1= generateTexture("driver/container.jpg");
    auto texture2= generateTexture("driver/awesomeface.png");

    // build and compile our shader program
    // ------------------------------------
    Shader ourShader("driver/test_camera/1box.vs", "driver/test_camera/inout.fs"); // you can name your shader files however you like
    ourShader.use();
    ourShader.setTextureUnit("texture1", texture1, 0);
    ourShader.setTextureUnit("texture2", texture2, 1);

    auto fn=[&](int frame)
    {
        ourShader.use();
        // render boxes
        glBindVertexArray(VAO);
            
        // create transformations
        glm::mat4 transform = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        
        transform = glm::rotate(transform, (float)glm::radians(frame+0.0f), glm::vec3(0.0f, 1.0f, 1.0f));
        transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, -0.0f));
        ourShader.setMat4("transform", transform);
        // now with the uniform matrix being replaced with new transformations, draw it again.
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // second transformation
        // ---------------------
        transform = glm::mat4(1.0f); // reset it to identity matrix
        transform = glm::translate(transform, glm::vec3(-0.5f, 0.5f, 0.0f));
        float scaleAmount = static_cast<float>(sin(glfwGetTime()));
        transform = glm::scale(transform, glm::vec3(scaleAmount, scaleAmount, scaleAmount));
        ourShader.setMat4("transform", transform);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    };

    PlayWindow(fn,20);

    glDeleteVertexArrays(1, &VAO);
    glDeleteProgram(ourShader.ID);
}

TEST_F(TestMVP, 6box)
{
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    // 1. 绑定VAO
    glBindVertexArray(VAO);
    // 2. 把顶点数组复制到缓冲中供OpenGL使用
    Gen6BoxVbo();
    // 3. 生成纹理
    auto texture1= generateTexture("driver/container.jpg");
    auto texture2= generateTexture("driver/awesomeface.png");

    // build and compile our shader program
    // ------------------------------------
    Shader ourShader("driver/test_camera/inout.vs", "driver/test_camera/inout.fs"); // you can name your shader files however you like
    ourShader.use();
    ourShader.setTextureUnit("texture1", texture1, 0);
    ourShader.setTextureUnit("texture2", texture2, 1);

    // create transformations
    glm::mat4 view          = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    view       = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    glm::mat4 projection    = glm::perspective(glm::radians(45.0f),800.0f/600.0f, 0.1f,100.0f);
    
    // pass transformation matrices to the shader
    ourShader.setMat4("projection", projection); // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
    ourShader.setMat4("view", view);

    // world space positions of our cubes
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    auto fn=[&](int frame)
    {
        ourShader.use();
        // render boxes
        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            
            model = glm::translate(model, cubePositions[i]);

            float angle = (i%3==0)?frame*10:20.0f*i;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

            ourShader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    };

    PlayWindow(fn,36);

    glDeleteVertexArrays(1, &VAO);
    glDeleteProgram(ourShader.ID);
}

TEST_F(TestMVP, camera)
{
    unsigned int VAO;
    glGenVertexArrays(1, &VAO);
    // 1. 绑定VAO
    glBindVertexArray(VAO);
    // 2. 把顶点数组复制到缓冲中供OpenGL使用
    Gen6BoxVbo();
    // 3. 生成纹理
    auto texture1= generateTexture("driver/container.jpg");
    auto texture2= generateTexture("driver/awesomeface.png");

    // build and compile our shader program
    // ------------------------------------
    Shader ourShader("driver/test_camera/inout.vs", "driver/test_camera/inout.fs"); // you can name your shader files however you like
    ourShader.use();
    ourShader.setTextureUnit("texture1", texture1, 0);
    ourShader.setTextureUnit("texture2", texture2, 1);

    // world space positions of our cubes
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f,  0.0f,  0.0f),
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };

    auto fn=[&](int frame)
    {
        ourShader.use();
        ourShader.setMat4("projection", m_camera.GetProjectionMatrix());
        ourShader.setMat4("view", m_camera.GetViewMatrix());

        // render boxes
        glBindVertexArray(VAO);


        for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);

            float angle = 20.0f * i+frame;
            model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));

            ourShader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
    };

    PlayWindow(fn,50);

    glDeleteVertexArrays(1, &VAO);
    glDeleteProgram(ourShader.ID);
}