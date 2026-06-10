#pragma once

#include "Mesh.h"
#include "Transform.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Object {
public:
    Mesh* mesh = nullptr;
    Transform transform;

protected:
    glm::vec3 initialPosition;
    glm::vec3 rotationPivot = glm::vec3(0.0f);

public:
    Object() = default;

    Object(const glm::vec3& initialPosition)
    {
        setInitialPosition(initialPosition);
    }

    virtual ~Object()
    {
        delete mesh;
    }

    void setInitialPosition(const glm::vec3& position)
    {
        this->initialPosition = position;
        this->transform.position = position;
    }

    glm::vec3 getInitialPosition() const
    {
        return initialPosition;
    }

    void setRotationPivot(const glm::vec3& pivot)
    {
        rotationPivot = pivot;
    }

    virtual void update(float deltaTime)
    {
    }

    virtual void draw(unsigned int shaderProgram)
    {
        if (mesh == nullptr)
        {
            return;
        }

        glm::mat4 model = glm::mat4(1.0f);

        model = glm::translate(model, transform.position);
        model = glm::translate(model, rotationPivot);

        model = glm::rotate(
            model,
            transform.rotation.y,
            glm::vec3(0.0f, 1.0f, 0.0f)
        );

        model = glm::translate(model, -rotationPivot);
        model = glm::scale(model, transform.scale);

        unsigned int modelLocation = glGetUniformLocation(shaderProgram, "model");

        glUniformMatrix4fv(
            modelLocation,
            1,
            GL_FALSE,
            glm::value_ptr(model)
        );

        mesh->draw();
    }
};
