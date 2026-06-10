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
// tworzenie obiektów

    auto gear = ObjectFactory::createObject(
        ObjectType::Gear,
        "Models/gear.obj",
        0.01f,
        1.0f,
        glm::vec3(0.0f, 0.0f, 0.0f)
    );

    auto gear_2 = ObjectFactory::createObject(
        ObjectType::Gear,
        "Models/gear_2.obj",
        0.01f,
        2.0f,
        glm::vec3(0.0f, 0.0f, 0.0f)
    );

    auto ratchet_spring = ObjectFactory::createObject(
        ObjectType::Gear,
        "Models/ratchet_spring.obj",
        0.01f,
        0.0f,
        glm::vec3(0.0f, 0.0f, 0.0f)
    );

    auto ratchet_key = ObjectFactory::createObject(
        ObjectType::Gear,
        "Models/ratchet_key.obj",
        0.01f,
        0.0f,
        glm::vec3(0.0f, 0.0f, 0.0f)
    );

    auto ratchet = ObjectFactory::createObject(
        ObjectType::Gear,
        "Models/ratchet.obj",
        0.01f,
        0.0f,
        glm::vec3(0.0f, 0.0f, 0.0f)
    );

    auto gear_5 = ObjectFactory::createObject(
        ObjectType::Gear,
        "Models/gear_5.obj",
        0.01f,
        4.0f,
        glm::vec3(0.0f, 0.0f, 0.0f)
    );

    auto gear_3 = ObjectFactory::createObject(
        ObjectType::Gear,
        "Models/gear_3.obj",
        0.01f,
        0.0f,
        glm::vec3(0.0f, 0.0f, 0.0f)
    );

    auto gear_6 = ObjectFactory::createObject(
        ObjectType::Gear,
        "Models/gear_6.obj",
        0.01f,
        3.0f,
        glm::vec3(0.0f, 0.0f, 0.0f)
    );

    auto gear_8 = ObjectFactory::createObject(
        ObjectType::Gear,
        "Models/gear_8.obj",
        0.01f,
        0.166666f,
        glm::vec3(0.0f, 0.0f, 0.0f)
    );

    auto dial = ObjectFactory::createObject(
        ObjectType::Gear,
        "Models/dial.obj",
        0.01f,
        0.0f,
        glm::vec3(0.0f, 0.0f, 0.0f)
    );

    auto frame = ObjectFactory::createObject(
        ObjectType::Gear,
        "Models/frame.obj",
        0.01f,
        0.0f,
        glm::vec3(0.0f, 0.0f, 0.0f)
    );

    auto frame_2 = ObjectFactory::createObject(
        ObjectType::Gear,
        "Models/frame_2.obj",
        0.01f,
        0.0f,
        glm::vec3(0.0f, 0.0f, 0.0f)
    );

    auto gear_1hour_gear = ObjectFactory::createObject(
        ObjectType::Gear,
        "Models/gear_1hour_gear.obj",
        0.01f,
        0.0f,
        glm::vec3(0.0f, 0.0f, 0.0f)
    );

    auto gear_7second_gear = ObjectFactory::createObject(
        ObjectType::Gear,
        "Models/gear_7second_gear.obj",
        0.01f,
        0.333333f,
        glm::vec3(0.0f, 0.0f, 0.0f)
    );

    auto housing_gear_4minute_gear = ObjectFactory::createObject(
        ObjectType::Gear,
        "Models/housing_gear_4minute_gear.obj",
        0.01f,
        0.0f,
        glm::vec3(0.0f, 0.0f, 0.0f)
    );

    auto new_escapement_gear_9 = ObjectFactory::createObject(
        ObjectType::Gear,
        "Models/new_escapement_gear_9.obj",
        0.01f,
        0.111111f,
        glm::vec3(0.0f, 0.0f, 0.0f)
    );

    auto new_mainspring = ObjectFactory::createObject(
        ObjectType::Gear,
        "Models/new_mainspring.obj",
        0.01f,
        0.0f,
        glm::vec3(0.0f, 0.0f, 0.0f)
    );

    auto new_palace = ObjectFactory::createObject(
        ObjectType::Gear,
        "Models/new_palace.obj",
        0.01f,
        0.0f,
        glm::vec3(0.0f, 0.0f, 0.0f)
    );

    auto ustawObrot = [](std::unique_ptr<Object>& object) {

    };

    ustawObrot(gear);
    ustawObrot(gear_2);
    ustawObrot(ratchet_spring);
    ustawObrot(ratchet_key);
    ustawObrot(ratchet);
    ustawObrot(gear_5);
    ustawObrot(gear_3);
    ustawObrot(gear_6);
    ustawObrot(gear_8);
    ustawObrot(dial);
    ustawObrot(frame);
    ustawObrot(frame_2);
    ustawObrot(gear_1hour_gear);
    ustawObrot(gear_7second_gear);
    ustawObrot(housing_gear_4minute_gear);
    ustawObrot(new_escapement_gear_9);
    ustawObrot(new_mainspring);
    ustawObrot(new_palace);

    objects.push_back(std::move(gear));
    objects.push_back(std::move(gear_2));
    objects.push_back(std::move(ratchet_spring));
    objects.push_back(std::move(ratchet_key));
    objects.push_back(std::move(ratchet));
    objects.push_back(std::move(gear_5));
    objects.push_back(std::move(gear_3));
    objects.push_back(std::move(gear_6));
    objects.push_back(std::move(gear_8));
    objects.push_back(std::move(dial));
    objects.push_back(std::move(frame));
    objects.push_back(std::move(frame_2));
    objects.push_back(std::move(gear_1hour_gear));
    objects.push_back(std::move(gear_7second_gear));
    objects.push_back(std::move(housing_gear_4minute_gear));
    objects.push_back(std::move(new_escapement_gear_9));
    objects.push_back(std::move(new_mainspring));
    objects.push_back(std::move(new_palace));


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


        glm::mat4 view = glm::lookAt(
            glm::vec3(0.0f, 5.0f, 0.0f), //kamera
            glm::vec3(0.0f, 0.0f, 0.0f), //punkt na który patrzy kamera
            glm::vec3(0.0f, 0.0f, 1.0f)  //góra kamery
        );

        glm::mat4 projection = glm::perspective(
            glm::radians(45.0f), //k¹t widzenia
            800.0f / 600.0f, //aspect ratio
            0.1f, //near plane
            100.0f //far plane
		);

		unsigned int viewloc = glGetUniformLocation(shaderProgram, "view");
        glUniformMatrix4fv(viewloc, 1, GL_FALSE, glm::value_ptr(view));

        unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

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