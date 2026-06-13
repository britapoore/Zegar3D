#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ObjFactory.h"
#include "Shader.h"
#include "ObjectsDefinition.h"

#include <iostream>
#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <cmath>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#define M_PI 3.14159265358979323846


// Zmienne kamery
glm::vec3 cameraPos   = glm::vec3(-1.0f, 5.0f, 0.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, -1.0f, 0.0f);
glm::vec3 cameraUp    = glm::vec3(0.0f, 0.0f,  1.0f);
float yaw   = -90.0f;
float pitch = 0.0f;

void processInput(GLFWwindow *window, float deltaTime)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    float cameraSpeed = 10.0f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        
    float rotationSpeed = 180.0f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        yaw -= rotationSpeed;
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        yaw += rotationSpeed;
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        pitch += rotationSpeed;
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        pitch -= rotationSpeed;
        
    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;
    
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.z = sin(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

unsigned int loadTexture(char const * path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    
    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cerr << "Nie udalo sie zaladowac tekstury: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}

int main()
{
    if (!glfwInit())
    {
        std::cerr << "Nie udalo sie zainicjalizowac GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(
        800, //szerokość
        600, //wysokość 
        "Zegar 3D", //nazwa okna 
        nullptr,
        nullptr
    );

    if (!window)
    {
        std::cerr << "Nie udalo sie utworzyc okna GLFW\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Nie udalo sie zainicjalizowac GLAD\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, 800, 600);
    glEnable(GL_DEPTH_TEST);

    unsigned int shaderProgram = createShaderProgram(); //tworzenie shadera

    std::vector<std::unique_ptr<Object>> objects; //tablica obiektów 

    unsigned int metalTex = loadTexture("Textures/metal.png");
    unsigned int goldTex = loadTexture("Textures/gold.png");
	// https://www.printables.com/model/588221-fully-3d-printed-mechanical-clock/comments żródło modeli 3D do zegara
	addObjects(objects, metalTex, goldTex); //dodawanie obiektów do tablicy



    for (auto& object : objects)
    {
        if (object == nullptr)
        {
            std::cerr << "Nie udalo sie utworzyc jednego z obiektow.\n";
            return -1;
        }
    }

    unsigned int depthMapFBO;
    glGenFramebuffers(1, &depthMapFBO);
    
    const unsigned int SHADOW_WIDTH = 2048, SHADOW_HEIGHT = 2048;
    unsigned int depthMap;
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL); //tworzenie tekstury
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
    float borderColor[] = { 1.0, 1.0, 1.0, 1.0 };
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
    
    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO); //mapa głębokości
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0); //tekstura 
    glDrawBuffer(GL_NONE);
    glReadBuffer(GL_NONE);
	glBindFramebuffer(GL_FRAMEBUFFER, 0); //renderujemy głębokość do tekstury, a nie do bufora ekranu

    unsigned int depthShaderProgram = createDepthShaderProgram();

    glm::vec3 lightPos(-5.0f, 10.0f, 5.0f);
    glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
    glm::vec3 objectColor(0.85f, 0.65f, 0.20f);

    glUseProgram(shaderProgram);
    glUniform1i(glGetUniformLocation(shaderProgram, "shadowMap"), 0);

    float lastTime = static_cast<float>(glfwGetTime());

    while (!glfwWindowShouldClose(window))
    {
        float currentTime = static_cast<float>(glfwGetTime());
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        processInput(window, deltaTime);

        for (auto& object : objects)
        {
            object->update(deltaTime);
        }

        glm::mat4 lightProjection, lightView;
        glm::mat4 lightSpaceMatrix;
        float near_plane = 1.0f, far_plane = 30.0f;
        lightProjection = glm::ortho(-15.0f, 15.0f, -15.0f, 15.0f, near_plane, far_plane);
        lightView = glm::lookAt(
			lightPos, //pozycja źródła światła
			glm::vec3(0.0f), //cel światła (środek sceny)
			glm::vec3(0.0, 1.0, 0.0) //wektor góry dla kamery światła
        );
        lightSpaceMatrix = lightProjection * lightView;

        glUseProgram(depthShaderProgram);
        glUniformMatrix4fv(glGetUniformLocation(depthShaderProgram, "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));

        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glClear(GL_DEPTH_BUFFER_BIT);
        for (auto& object : objects)
        {
            object->draw(depthShaderProgram);
        }
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        glViewport(0, 0, 1400, 1200);
        glClearColor(1.0f, 1.0f, 1.00f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);

        glm::mat4 view = glm::lookAt(
            cameraPos, 
            cameraPos + cameraFront, 
            cameraUp  
        );

        glm::mat4 projection = glm::perspective(
            glm::radians(45.0f), //kat widzenia
            800.0f / 600.0f, //aspect ratio
            0.1f, //near plane
            100.0f //far plane
        );

        //wysłanie danych do shadera
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));
        
        glUniform3fv(glGetUniformLocation(shaderProgram, "lightPos"), 1, glm::value_ptr(lightPos));
        glUniform3fv(glGetUniformLocation(shaderProgram, "viewPos"), 1, glm::value_ptr(cameraPos));
        glUniform3fv(glGetUniformLocation(shaderProgram, "lightColor"), 1, glm::value_ptr(lightColor));
        glUniform3fv(glGetUniformLocation(shaderProgram, "objectColor"), 1, glm::value_ptr(objectColor));
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "lightSpaceMatrix"), 1, GL_FALSE, glm::value_ptr(lightSpaceMatrix));

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, depthMap);

        for (auto& object : objects)
        {
            object->draw(shaderProgram);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
