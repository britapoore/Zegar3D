#pragma once

#include "Object.h"
#include "Types.h"

#include <memory>
#include <string>
#include <glm/glm.hpp>

class ObjectFactory
{
public:
    static std::unique_ptr<Object> createObject(
        ObjectType type,
        const std::string& objPath,
        float scale,
        float rotationSpeed,
        const glm::vec3& initialPosition = glm::vec3(0.0f, 0.0f, 0.0f)
    );
};