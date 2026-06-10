#include "Gear.h"

Gear::Gear(std::vector<float>& vertices, std::vector<unsigned int>& indices, float rotationSpeed)
{
    this->mesh = new Mesh(vertices, indices);
    this->rotationSpeed = rotationSpeed;

    this->transform.position = glm::vec3(0.0f, 0.0f, 0.0f);
    this->transform.rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    this->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f);
}


void Gear::draw()
{
    mesh->draw();
}