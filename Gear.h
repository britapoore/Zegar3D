#pragma once
#include "Object.h"

class Gear : public Object {
private:
    float rotationSpeed;

public:
    Gear(std::vector<float>& vertices, std::vector<unsigned int>& indices, float rotationSpeed);

    void update(float deltaTime) override {
        transform.rotation.z += rotationSpeed * deltaTime;
    }

    void draw() override;
};