#pragma once
#include "Mesh.h"
#include "Transform.h"

class Object {
public:
    Mesh* mesh;
    Transform transform;

    virtual ~Object() {
        delete mesh;
    }

    virtual void update(float deltaTime) {}
    virtual void draw() {};
};