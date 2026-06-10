#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glad/glad.h>


class Mesh {
public:
    unsigned int VAO, VBO, EBO;
    int indicesCount;

    Mesh(std::vector<float>& vertices, std::vector<unsigned int>& indices);
    void draw();
};