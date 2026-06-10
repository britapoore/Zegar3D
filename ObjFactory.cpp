#include "ObjFactory.h"

#include "ObjLoader.h"
#include "Gear.h"

#include <iostream>

std::unique_ptr<Object> ObjectFactory::createObject(
    ObjectType type,
    const std::string& objPath,
    float scale,
    float rotationSpeed,
    const glm::vec3& initialPosition
)
{
    ObjData objData = ObjLoader::load(objPath, scale);

    if (objData.vertices.empty() || objData.indices.empty())
    {
        std::cerr << "Nie mozna utworzyc obiektu. OBJ pusty albo bledny: "
            << objPath << std::endl;

        return nullptr;
    }

    switch (type) //fabryka obiektów (typ)
    {
        case ObjectType::Gear:
            return std::make_unique<Gear>(
                objData.vertices,
                objData.indices,
                rotationSpeed,
                initialPosition,
                glm::vec3(objData.center.x, objData.center.y, objData.center.z)
            );

        default:
        {
            std::unique_ptr<Object> object = std::make_unique<Object>(initialPosition);
            object->mesh = new Mesh(objData.vertices, objData.indices);
            object->setRotationPivot(
                glm::vec3(objData.center.x, objData.center.y, objData.center.z)
            );
            return object;
        }
    }
}
