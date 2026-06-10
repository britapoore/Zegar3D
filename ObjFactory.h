#pragma once
#include "Object.h"
#include "Types.h"

#include <memory>
#include <string>

class ObjectFactory
{
public:
    static std::unique_ptr<Object> createObject(
        ObjectType type,
        const std::string& objPath,
        float scale,
        float rotationSpeed = 0.0f
    );
};