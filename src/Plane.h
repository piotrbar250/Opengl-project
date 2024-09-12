#pragma once
#include <iostream>
#include <vector>
#include <random>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

#include "stb_image.h"
#include "Bezier.h"
#include "AssimpObject.h"

#include "config.h"

using namespace std;

random_device rd;
mt19937 gen(rd());
uniform_real_distribution<> dis(0.0f, 1.0f);


class Plane
{
public:
    Shader shader;
    unsigned int VAO, VBO, EBO;
    glm::mat4 model;
    Bezier bezier;
    int vertexCount = 0;
    float denX, denY;
    bool gourand = false;
    AssimpObject tree;
    vector<glm::vec3> treePos;
    // Plane(const char* vertexPath = "../res/vertexPlane.glsl", const char* fragmentPath = "../res/fragmentPlane.glsl")
    Plane(const char* vertexPath = "../res/vertexAssimpView.glsl", const char* fragmentPath = "../res/fragmentAssimpView.glsl")
        : shader(vertexPath, fragmentPath), model(glm::mat4(1.0f)),
        tree("../res/vertexAssimpView.glsl", "../res/fragmentAssimpView.glsl", "../res/coconut-tree-obj/coconutTree.obj")
    {
                treePos.resize(4);
       
        for(int i = 0; i < 4; i++)
            treePos[i] = glm::vec3(dis(gen), 0.0f, dis(gen));
        // float r = 5.0f;
        // denX = 10.0f;
        // denY = 10.0f;

        // float vertices[] = {
        //     -r, 0.0f, r, 
        //     -r, 0.0f, -r,
        //     r, 0.0f, r,

        //     r, 0.0f, r,
        //     r, 0.0f, -r,
        //     -r, 0.0f, -r,
        // };

        vector<float> vertices;

        float d = 1.f;
        float p = 100.0f;
        float l = d / p;

        float Z = 0.0f;
        float X = 0.0f;

        // for(int z = 0; z < 5; z++)
        // {
        //     X = 0.0f;
        //     for(int x = 0; x < 5; x++)
        //     {
        //         vertexCount += 6;

        //         vertices.push_back(X);
        //         vertices.push_back(0.0f);
        //         vertices.push_back(-Z);

        //         vertices.push_back(X + l);
        //         vertices.push_back(0.0f);
        //         vertices.push_back(-Z);

        //         vertices.push_back(X);
        //         vertices.push_back(0.0f);
        //         vertices.push_back(-(Z + l));

        //         vertices.push_back(X);
        //         vertices.push_back(0.0f);
        //         vertices.push_back(-(Z + l));

        //         vertices.push_back(X + l);
        //         vertices.push_back(0.0f);
        //         vertices.push_back(-(Z + l));

        //         vertices.push_back(X + l);
        //         vertices.push_back(0.0f);
        //         vertices.push_back(-Z);

        //         X += l;
        //     }
        //     Z += l;
        // }

        // for(int z = 0; z < p; z++)
        // {
        //     X = 0.0f;
        //     for(int x = 0; x < p; x++)
        //     {
        //         vertexCount += 6;

        //         vertices.push_back(X);
        //         vertices.push_back(bezier.z(X, Z));
        //         vertices.push_back(Z);

        //         vertices.push_back(X + l);
        //         vertices.push_back(bezier.z(X+l, Z));
        //         vertices.push_back(Z);

        //         vertices.push_back(X);
        //         vertices.push_back(bezier.z(X, Z+l));
        //         vertices.push_back((Z + l));

        //         vertices.push_back(X);
        //         vertices.push_back(bezier.z(X, Z+l));
        //         vertices.push_back((Z + l));

        //         vertices.push_back(X + l);
        //         vertices.push_back(bezier.z(X+l, Z+l));
        //         vertices.push_back((Z + l));

        //         vertices.push_back(X + l);
        //         vertices.push_back(bezier.z(X+l, Z));
        //         vertices.push_back(Z);

        //         X += l;
        //     }
        //     Z += l;
        // }

        for(int z = 0; z < p; z++)
        {
            X = 0.0f;
            for(int x = 0; x < p; x++)
            {
                vertexCount += 6;

                glm::vec3 nor;

                vertices.push_back(X);
                vertices.push_back(bezier.z(X, Z));
                vertices.push_back(Z);
                nor = -bezier.normal(X, Z);
                vertices.push_back(nor.x);
                vertices.push_back(nor.y);
                vertices.push_back(nor.z);
                vertices.push_back(X);
                vertices.push_back(Z);

                vertices.push_back(X + l);
                vertices.push_back(bezier.z(X+l, Z));
                vertices.push_back(Z);
                nor = -bezier.normal(X+l, Z);
                vertices.push_back(nor.x);
                vertices.push_back(nor.y);
                vertices.push_back(nor.z);
                vertices.push_back(X+l);
                vertices.push_back(Z);

                vertices.push_back(X);
                vertices.push_back(bezier.z(X, Z+l));
                vertices.push_back((Z + l));
                nor = -bezier.normal(X, Z+l);
                vertices.push_back(nor.x);
                vertices.push_back(nor.y);
                vertices.push_back(nor.z);
                vertices.push_back(X);
                vertices.push_back(Z+l);

                vertices.push_back(X);
                vertices.push_back(bezier.z(X, Z+l));
                vertices.push_back((Z + l));
                nor = -bezier.normal(X, Z+l);
                vertices.push_back(nor.x);
                vertices.push_back(nor.y);
                vertices.push_back(nor.z);
                vertices.push_back(X);
                vertices.push_back(Z+l);

                vertices.push_back(X + l);
                vertices.push_back(bezier.z(X+l, Z+l));
                vertices.push_back((Z + l));
                nor = -bezier.normal(X+l, Z+l);
                vertices.push_back(nor.x);
                vertices.push_back(nor.y);
                vertices.push_back(nor.z);
                vertices.push_back(X+l);
                vertices.push_back(Z+l);

                vertices.push_back(X + l);
                vertices.push_back(bezier.z(X+l, Z));
                vertices.push_back(Z);
                nor = -bezier.normal(X+l, Z);
                vertices.push_back(nor.x);
                vertices.push_back(nor.y);
                vertices.push_back(nor.z);
                vertices.push_back(X+l);
                vertices.push_back(Z);

                X += l;
            }
            Z += l;
        }

        // for(int i = 0; i < vertices.size(); i += 6)
        // {
        //     cout << vertices[i] << " " << vertices[i+1] << " " << vertices[i+2] << endl;
        //     cout << vertices[i+3] << " " << vertices[i+4] << " " << vertices[i+5] << endl;
        // }


        cout << vertexCount << endl;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);
        
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, vertexCount * 8 * sizeof(float), vertices.data(), GL_STATIC_DRAW);
        

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);


        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));
        glEnableVertexAttribArray(2);

        glBindVertexArray(0);

        shader.use();
        shader.setVec3("objectColor", 1.0f, 0.5f, 0.31f);
        shader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
        shader.setBool("gourand", gourand);       // shader.use();
        shader.setInt("texture_diffuse1", 0);
        // shader.setInt("texture2", 1);
    }


    void draw(glm::mat4& view, glm::mat4& projection, glm::mat4 model, glm::vec3 lightPos, glm::vec3 lightPosJet, glm::vec3 targetPos)
    {

        shader.use();
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);
        shader.setMat4("model", model);
        shader.setVec3("lightPos", lightPos);

        shader.setVec3("lightSources[0].pos", glm::vec3(view * glm::vec4(lightPosJet, 1.0f)));
        shader.setVec3("lightSources[0].color", 1.0f, 0.0f, 0.0f);

        shader.setVec3("lightSources[1].pos",  glm::vec3(view * glm::vec4(lightPos, 1.0f)));
        shader.setVec3("lightSources[1].color", 1.0f, 1.0f, 1.0f);

        glm::vec3 spotlightDirection = glm::normalize(targetPos - lightPosJet);
        shader.setVec3("lightSources[0].direction", glm::vec3(view * glm::vec4(spotlightDirection, 0.0f)));

        float innerCutOff = glm::cos(glm::radians(12.5f));
        float outerCutOff = glm::cos(glm::radians(17.5f));

        shader.setFloat("lightSources[0].cutOff", innerCutOff);
        shader.setFloat("lightSources[0].outerCutOff", outerCutOff);

        shader.setFloat("fogDensity", fogDensity);

        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES, 0, vertexCount);

         for(int i = 0; i < 4; i++)
            tree.draw(view, projection, model * glm::translate(glm::mat4(1.0f), glm::vec3(treePos[i].x, bezier.z(treePos[i].x, treePos[i].z), treePos[i].z)) * glm::scale(glm::mat4(1.0f), glm::vec3(0.0005f)), lightPos, lightPosJet, targetPos);
    }
};