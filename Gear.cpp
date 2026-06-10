#include "Gear.h"

Gear::Gear(
    std::vector<float>& vertices,
    std::vector<unsigned int>& indices,
    float rotationSpeed,
    const glm::vec3& initialPosition
)
    : Object(initialPosition)
{
    this->mesh = new Mesh(vertices, indices);
    this->rotationSpeed = rotationSpeed;
}

void Gear::update(float deltaTime)
{
    transform.rotation.z += rotationSpeed * deltaTime;
}