#pragma once
#include "Object.h"
#include <vector>
#include <glm/glm.hpp>

class Pendulum : public Object {
private: 
    float period, amplitude, time;
public:
    Pendulum(
        std::vector<float>& vertices,
        std::vector<unsigned int>& indices,
		float period,
        const glm::vec3& initialPosition = glm::vec3(0.0f, 0.0f, 0.0f),
        const glm::vec3& rotationPivot = glm::vec3(0.0f, 0.0f, 0.0f)
    );
	void update(float deltaTime) override;
};
