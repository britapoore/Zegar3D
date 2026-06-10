#include "Gear.h"

Gear::Gear(
    std::vector<float>& vertices,
    std::vector<unsigned int>& indices,
    float rotationSpeed,
    const glm::vec3& initialPosition,
    const glm::vec3& rotationPivot
)
    : Object(initialPosition)
{
    this->mesh = new Mesh(vertices, indices);
    this->rotationSpeed = rotationSpeed;
    setRotationPivot(rotationPivot);
}

void Gear::update(float deltaTime)
{
    transform.rotation.y += rotationSpeed * deltaTime;
}
