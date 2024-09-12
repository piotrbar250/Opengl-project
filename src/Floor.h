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

class Floor
{
public:
    Shader shader;
    unsigned int VAO, VBO, EBO;
    unsigned int vertexCount;
    glm::mat4 model;

    Floor()
        : shader("../res/vertexFloor.glsl", "../res/fragmentFloor.glsl"), model(glm::mat4(1.0f))
    {

        float r = 3.0f;

        float vertices[] = {
            -r, 0.0f, -r,         0.0f, 0.0f,  // bottom left
            -r, 0.0f, r,          0.0f, 1.0f,   // top left
            r, 0.0f, -r,          1.0f, 0.0f,   // bottom right
            r, 0.0f, r,           1.0f, 1.0f,    // top right
        };

        unsigned int indices[] = {
            0, 1, 2,
            1, 2, 3
        };


        vertexCount = sizeof(indices) / sizeof(int);
        cout << "vertexCount " << vertexCount << endl;

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3*sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindVertexArray(0);

        shader.use();
        shader.setInt("texture1", 0);
        shader.setInt("texture2", 1);
    }

    void draw(glm::mat4& view, glm::mat4& projection)
    {
        shader.use();
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);
        shader.setMat4("model", model);

        glBindVertexArray(VAO);
       glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, 0);
    }

    void draw(glm::mat4& view, glm::mat4& projection, glm::mat4 model)
    {
        shader.use();
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);
        shader.setMat4("model", model);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, vertexCount, GL_UNSIGNED_INT, 0);
    }
};