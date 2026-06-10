#pragma once
#include "Object.h"
#include <vector>
#include <glm/glm.hpp>


class Gear : public Object {
private:
    float rotationSpeed;

public:
    Gear(
        std::vector<float>& vertices,
        std::vector<unsigned int>& indices, 
        float rotationSpeed,
        const glm::vec3& initialPosition = glm::vec3(0.0f, 0.0f, 0.0f),
        const glm::vec3& rotationPivot = glm::vec3(0.0f, 0.0f, 0.0f)
    );

    void update(float deltaTime) override;
};
