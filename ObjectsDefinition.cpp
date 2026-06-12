#pragma once
#include "ObjFactory.h"
#include "ObjectsDefinition.h"

#define M_PI 3.14159265358979323846

//tworzenie obiekt�w 

void addObjects(std::vector<std::unique_ptr<Object>>& objects, unsigned int metalTex, unsigned int goldTex) {
    auto gear_2 = ObjectFactory::createObject(
        ObjectType::Gear,
        "Models/gear_2.obj",
        0.01f,
        -M_PI / 4320.0f,
        glm::vec3(0.0f, 0.0f, 0.0f)
    );

    auto ratchet_spring = ObjectFactory::createObject(
        ObjectType::Gear,
        "Models/ratchet_spring.obj",
        0.01f,
        0.0f,
        glm::vec3(0.0f, 0.0f, 0.0f)
    );


    auto gear_5 = ObjectFactory::createObject(
        ObjectType::Gear,
        "Models/gear_5.obj",
        0.01f,
        M_PI / 360.0f,
        glm::vec3(0.0f, 0.0f, 0.0f)
    );

    auto gear_3 = ObjectFactory::createObject(
        ObjectType::Gear,
        "Models/gear_3.obj",
        0.01f,
        M_PI / 1080.0f,
        glm::vec3(0.0f, 0.0f, 0.0f)
    );

    auto gear_6 = ObjectFactory::createObject(
        ObjectType::Gear,
        "Models/gear_6.obj",
        0.01f,
        -M_PI / 120.0f,
        glm::vec3(0.0f, 0.0f, 0.0f)
    );

    auto gear_8 = ObjectFactory::createObject(
        ObjectType::Gear,
        "Models/gear_8.obj",
        0.01f,
        -M_PI / 6.0f,
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
        M_PI / 12960.0f,
        glm::vec3(0.0f, 0.0f, 0.0f)
    );

    auto gear_7second_gear = ObjectFactory::createObject(
        ObjectType::Gear,
        "Models/gear_7second_gear.obj",
        0.01f,
        M_PI / 30.0f,
        glm::vec3(0.0f, 0.0f, 0.0f)
    );

    auto housing_gear_4minute_gear = ObjectFactory::createObject(
        ObjectType::Gear,
        "Models/housing_gear_4minute_gear.obj",
        0.01f,
        -M_PI / 1080.0f,
        glm::vec3(0.0f, 0.0f, 0.0f)
    );

    auto new_escapement_gear_9 = ObjectFactory::createObject(
        ObjectType::Gear,
        "Models/new_escapement_gear_9.obj",
        0.01f,
        M_PI / 9.0f,
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
        ObjectType::Pendulum,
        "Models/new_palace.obj",
        0.01f,
        1.2f,
        glm::vec3(0.0f, 0.0f, 0.0f)
    );

        gear_2->textureID = metalTex; gear_2->hasTexture = true;
    ratchet_spring->textureID = metalTex; ratchet_spring->hasTexture = true;
    gear_5->textureID = metalTex; gear_5->hasTexture = true;
    gear_3->textureID = metalTex; gear_3->hasTexture = true;
    gear_6->textureID = metalTex; gear_6->hasTexture = true;
    gear_8->textureID = metalTex; gear_8->hasTexture = true;
    dial->textureID = goldTex; dial->hasTexture = true;
    frame->textureID = goldTex; frame->hasTexture = true;
    frame_2->textureID = goldTex; frame_2->hasTexture = true;
    gear_1hour_gear->textureID = metalTex; gear_1hour_gear->hasTexture = true;
    gear_7second_gear->textureID = metalTex; gear_7second_gear->hasTexture = true;
    housing_gear_4minute_gear->textureID = metalTex; housing_gear_4minute_gear->hasTexture = true;
    new_escapement_gear_9->textureID = metalTex; new_escapement_gear_9->hasTexture = true;
    new_mainspring->textureID = metalTex; new_mainspring->hasTexture = true;
    new_palace->textureID = metalTex; new_palace->hasTexture = true;
    objects.push_back(std::move(gear_2));
    objects.push_back(std::move(ratchet_spring));
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

}


