#include <iostream>
#include <chrono>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "imgui_internal.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Camera.h"

#include "Triangle.h"
#include "Rectangle.h"
#include "Cube.h"
#include "Floor.h"
#include "YAxis.h"
#include "LightningScene.h"
#include "Plane.h"

#include "UI.h"

#include "WindowSetup.h"

// #include "Model-loading/Model.h"
#include "AssimpObject.h"
#include "Textures.h"
#include "stb_image.h"

using namespace std;
using namespace glm;


void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);


// Camera camera(glm::vec3(0.0f, 1.0f, 3.0f));
Camera camera(glm::vec3(0.0f, 1.0f, 0.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = false;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

vec3 lightPosCast(1.2f, 0.0f, 2.0f);
vec3 lightPos(1.2f, 1.0f, 2.0f);
vec3 lightPosJet(1.2f, 1.0f, 2.0f);

vec3 jetPos;

float flightAngle;

mat4 getCirclingModelMatrix(vec3 translation)
{
    mat4 model = mat4(1.0f);
    float angle = glfwGetTime();
    float radius = 3.0f;
    // vec3 translation = vec3(1.2f, 1.0f, 2.0f);

    float rx = cos(angle) * radius;
    float rz = sin(angle) * radius;
    model = translate(model, vec3(rx, 0.0f, rz) + translation);
    // lightPos = vec3(rx, 0.0f, rz) + translation;
    return model;
}

mat4 getSunModelMatrix(vec3 translation)
{
    mat4 model = mat4(1.0f);
    float angle = glfwGetTime();
    float radius = 3.0f;
    // vec3 translation = vec3(1.2f, 1.0f, 2.0f);

    float rz = cos(angle) * radius;
    float ry = sin(angle) * radius;
    model = translate(model, vec3(0.0, ry, rz) + translation);
    lightPos = vec3(0.0f, ry,  rz) + translation;
    return model;
}

mat4 getJetModelMatrix()
{
    mat4 model = mat4(1.0f);
    float angle = -glfwGetTime() / 2.0f;
    float radius = 3.0f;

    float rx = cos(angle) * radius;
    float rz = sin(angle) * radius;

    model = translate(model, vec3(rx, 0.0, rz));

    flightAngle = atan2(rz, rx);
    jetPos = vec3(rx, 0.0, rz);
    lightPosJet = vec3(rx, 1.0, rz);
    return model;
}


auto lastTime = std::chrono::high_resolution_clock::now();
int frameCount = 0;

void displayFPS() 
{
	auto currentTime = std::chrono::high_resolution_clock::now();
	double timeInterval = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - lastTime).count();
	frameCount++;

	if (timeInterval >= 2.0) {
		std::cout << "FPS: " << frameCount << std::endl;
		frameCount = 0;
		lastTime = currentTime;
	}
}

int main()
{
    GLFWwindow *window = windowSetup();

    glfwMakeContextCurrent(window);
    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // glfwSwapInterval(1);

    gladSetup(window);

    // glLineWidth(5.0f);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    
    unsigned int texture1 = textureContainer();
    unsigned int texture2 = textureAwesomeFace();
    unsigned int texture3 = textureSand();
    
    const char* vertexPath = "../res/vertexCubeLightning.glsl";
    const char* fragmentPath = "../res/fragmentCubeLightning.glsl";

    // Triangle t1;
    // Rectangle r1, r2;
    
    Cube c1;
    // Cube c1(vertexPath, fragmentPath);
    Floor f1;
    YAxis l1, l2; // l2(1.2, 30, 2.0);
    LightningScene ls1;
    AssimpObject jet("../res/vertexAssimpView.glsl", "../res/fragmentAssimpView.glsl", "../res/hawker_900_xp.zip/anadolu_jet.obj");
    AssimpObject tree("../res/vertexAssimpView.glsl", "../res/fragmentAssimpView.glsl", "../res/coconut-tree-obj/coconutTree.obj");
    Plane p1;

    mat4 transform = mat4(1.0f);

    mat4 model = mat4(1.0f);
    mat4 view = mat4(1.0f);
    mat4 projection = mat4(1.0f);

    view = translate(mat4(1.0f), vec3(0.0f, 0.0f, -3.0f));
    projection = perspective(radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

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


    mat4 rot = mat4(1.0f);
    mat4 trans = mat4(1.0f);

    // ls1.changeLightningModel();
    bool simulation = false;

    while (!glfwWindowShouldClose(window))
    {        
        displayFPS();
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);


        if(glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
            ls1.changeLightningModel();

        // glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 
        // TEXTURES

        // glActiveTexture(GL_TEXTURE0);
        // glBindTexture(GL_TEXTURE_2D, texture1);
        
        // glActiveTexture(GL_TEXTURE1);
        // glBindTexture(GL_TEXTURE_2D, texture2);

        // RENDERING

        mat4 localJetModel = getJetModelMatrix();

        mat4 jetModel = translate(mat4(1.0f), vec3(0.0f, 1.0f, 0.0f)) * localJetModel * rotate(mat4(1.0f),  -flightAngle, vec3(0.0f, 1.0f, 0.0f)) * scale(mat4(1.0f), vec3(0.1f));
        
        if(cameraMode == CAMERA_FREE)
        {
            view = camera.GetViewMatrix();
        }
        else if(cameraMode == CAMERA_COCKPIT)
        {
            camera.Position = jetPos + vec3(0.0f, 0.5f, 0.0f);
            view = camera.GetViewMatrix();
        }
        else if(cameraMode == CAMERA_FOLLOWING)
        {
            camera.Position = jetPos + vec3(0.0f, 1.0f, 0.0f);
            view = lookAt(camera.Position + normalize(vec3(-jetPos.z, 0.0f, jetPos.x)) * 2.0f, camera.Position, vec3(0.0f, 1.0f, 0.0f));
        }
        
        projection = perspective(radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

        glm::vec3 targetPos = glm::vec3(-0.5f, 0.0f, 0.5f);

        // getCirclingModelMatrix(vec3(0, 0, 0));
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture3);
        ls1.drawLightCube(view, projection, getSunModelMatrix(vec3(lightPosCast.x, 0.0f, lightPosCast.z)) * scale(mat4(1.0f), vec3(0.2f)));
        p1.draw(view, projection, mat4(1.0f), lightPos, lightPosJet, targetPos);
        p1.draw(view, projection, translate(mat4(1.0f), vec3(1.0f, 0.0f, 0.0f)), lightPos, lightPosJet, targetPos);
        p1.draw(view, projection, translate(mat4(1.0f), vec3(2.0f, 0.0f, 0.0f)), lightPos, lightPosJet, targetPos);
        p1.draw(view, projection, translate(mat4(1.0f), vec3(-1.0f, 0.0f, 0.0f)), lightPos, lightPosJet, targetPos);
        p1.draw(view, projection, translate(mat4(1.0f), vec3(-2.0f, 0.0f, 0.0f)), lightPos, lightPosJet, targetPos);
        p1.draw(view, projection, translate(mat4(1.0f), vec3(-3.0f, 0.0f, 0.0f)), lightPos, lightPosJet, targetPos);
        // p1.draw(view, projection, scale(mat4(1.0f), vec3(0.0f, 0.0f, -1.0f)), lightPos);


        // jet.draw(view, projection, mat4(1.0f) * rotate(mat4(1.0f), radians(180.0f), vec3(0.0f, 1.0f, 0.0f)), lightPos);
        // jet.draw(view, projection, mat4(1.0f) * rotate(mat4(1.0f),  radians(-90.0f), vec3(1.0f, 0.0f, 0.0f)) * scale(mat4(1.0f), vec3(0.002f)), lightPos);

        
        jet.draw(view, projection, jetModel, lightPos, lightPosJet, targetPos);
        tree.draw(view, projection, scale(mat4(1.0f), vec3(0.0005f)), lightPos, lightPosJet, targetPos);
        // jet.draw(view, projection, mat4(1.0f) * rotate(mat4(1.0f),  radians(0.0f), vec3(1.0f, 0.0f, 0.0f)) * scale(mat4(1.0f), vec3(0.1f)), lightPos);

        // ls1.drawLightCube(view, projection, translate(mat4(1.0f), lightPos) * scale(mat4(1.0f), vec3(0.2f)));
        // ls1.drawCube(view, projection, translate(mat4(1.0f), vec3(0.0f, 0.5f, 0.0f)), lightPos, camera.Position);

        // ls1.drawLightCube(view, projection, getCirclingModelMatrix(lightPos) * scale(mat4(1.0f), vec3(0.2f)));
        // l1.draw(view, projection, mat4(1.0f));
        // l2.draw(view, projection, translate(mat4(1.0f), lightPos));
        
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        
        // glActiveTexture(GL_TEXTURE1);
        // glBindTexture(GL_TEXTURE_2D, texture2);
        f1.draw(view, projection, mat4(1.0f));

        // c1.updatePos();
        // c1.draw(view, projection);

        // for(int i = 0; i < 10; i++)
        // {
        //    mat4 model = translate(mat4(1.0f), cubePositions[i]) * rotate(mat4(1.0f), (float)glfwGetTime(), vec3(1.0f, 1.0f, 1.0f));
        //     c1.draw(view, projection, model);
        // }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // simulation = ToggleSwitch("Toggle", simulation);
        RadioButtonSections();


        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());



        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);    
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    if(MENU)
        return;
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_M && action == GLFW_PRESS)
    {
        if(!MENU)
        {
            MENU = true;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        else
        {
            MENU = false;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }
}