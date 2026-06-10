#include "ObjFactory.h"
#include "ObjLoader.h"
#include "Gear.h"
#include <iostream>

std::unique_ptr<Object> ObjectFactory::createObject(
    ObjectType type,
    const std::string& objPath,
    float scale,
    float rotationSpeed
)
{
    ObjData objData = ObjLoader::load(objPath, scale);

    if (objData.vertices.empty() || objData.indices.empty())
    {
        std::cerr << "Nie mozna utworzyc obiektu. OBJ pusty albo bledny: "
            << objPath << std::endl;
        return nullptr;
    }

    switch (type)
    {
    case ObjectType::Gear:
        return std::make_unique<Gear>(
            objData.vertices,
            objData.indices,
            rotationSpeed
        );

    case ObjectType::StaticObject:
    default:
    {
        std::unique_ptr<Object> object = std::make_unique<Object>();
        object->mesh = new Mesh(objData.vertices, objData.indices);
        object->transform.position = glm::vec3(0.0f, 0.0f, 0.0f);
        object->transform.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
        object->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f);
        return object;
    }
    }
}