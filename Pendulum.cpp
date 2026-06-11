#include "Pendulum.h"
#include <math.h>

Pendulum::Pendulum(
    std::vector<float>& vertices,
    std::vector<unsigned int>& indices,
    float period,
    const glm::vec3& initialPosition,
    const glm::vec3& rotationPivot
)
    : Object(initialPosition)
{
    this->mesh = new Mesh(vertices, indices);
    this->period = period;
    this->amplitude = glm::radians(15.0f);
    this->time = 0.0f;
    setRotationPivot(rotationPivot);
}

void Pendulum::update(float deltaTime)
{
	time += deltaTime;
    float omega = 2.0f * 3.1415926535f / period;
    transform.rotation.y = amplitude * sin(omega * time);
}
