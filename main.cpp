#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ObjFactory.h"
#include "Shader.h"

#include <iostream>
#include <vector>
#include <memory>

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
        800, //szerokoœæ
        600, //wysokoœæ 
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


    //tworzenie obiektów 
    auto gear1 = ObjectFactory::createObject(
        ObjectType::Gear, //object type (class)
        "Models/gear.obj", //path to model
        0.01f, //scale
        1.0f, //rotation speed
        glm::vec3(-0.5f, 0.0f, 0.0f) //initial position
    );

    auto gear2 = ObjectFactory::createObject(
        ObjectType::Gear,
        "Models/gear_2.obj",
        0.01f,
        0.0f,
        glm::vec3(0.0f, 0.0f, 0.0f)
    );
    auto gear3 = ObjectFactory::createObject(
        ObjectType::Gear,
        "Models/gear_3.obj",
        0.01f,
        0.0f,
        glm::vec3(0.0f, 0.0f, 0.0f)
    );
    auto gear5 = ObjectFactory::createObject(
        ObjectType::Gear,
        "Models/gear_5.obj",
        0.01f,
        0.0f,
        glm::vec3(0.0f, 0.0f, 0.0f)
    );
    auto gear6 = ObjectFactory::createObject(
        ObjectType::Gear,
        "Models/gear_6.obj",
        0.01f,
        0.0f,
        glm::vec3(0.0f, 0.0f, 0.0f)
    );
    auto gear8 = ObjectFactory::createObject(
        ObjectType::Gear,
        "Models/gear_8.obj",
        0.01f,
        0.0f,
        glm::vec3(0.0f, 0.0f, 0.0f)
    );

    objects.push_back(std::move(gear1));
    objects.push_back(std::move(gear2));
    objects.push_back(std::move(gear3));
    objects.push_back(std::move(gear5));
    objects.push_back(std::move(gear6));
    objects.push_back(std::move(gear8));


    for (auto& object : objects)
    {
        if (object == nullptr)
        {
            std::cerr << "Nie udalo sie utworzyc jednego z obiektow.\n";
            return -1;
        }
    }

    float lastTime = static_cast<float>(glfwGetTime());

    while (!glfwWindowShouldClose(window))
    {
        float currentTime = static_cast<float>(glfwGetTime());
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        glClearColor(0.1f, 1.0f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);




        for (auto& object : objects)
        {
            object->update(deltaTime);
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