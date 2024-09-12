#pragma once
#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

#include "stb_image.h"

using namespace std;

class YAxis
{
public:
    Shader shader;
    unsigned int VAO, VBO, EBO;
    unsigned int vertexCount;
    glm::mat4 model;

    YAxis(float x = 0.0f, float y = 30.0f, float z = 0.0f)
        : shader("../res/vertexYAxis.glsl", "../res/fragmentYAxis.glsl"), model(glm::mat4(1.0f))
    {

        float r = 30.0f;

        float vertices[] = {
            x, -r, z,
            x, r, z
        };

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);

        shader.use();
    }

    void draw(glm::mat4& view, glm::mat4& projection)
    {
        shader.use();
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);
        shader.setMat4("model", model);

        glBindVertexArray(VAO);
        glDrawArrays(GL_LINES, 0, 2);
    }

    void draw(glm::mat4& view, glm::mat4& projection, glm::mat4 model)
    {
        shader.use();
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);
        shader.setMat4("model", model);

        glBindVertexArray(VAO);
        // glDrawArrays(GL_LINES, 0, 2);
        glDepthMask(GL_FALSE);  // Disable depth writing
        // Draw Y-axis line
        glDrawArrays(GL_LINES, 0, 2);
        glDepthMask(GL_TRUE);   // Enable depth writing again

    }
};