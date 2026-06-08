#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <vector>
#include <cmath>

const float PI = 3.14159265358979323f;


struct Vec2
{
    float x, y;
};

struct Vec3
{
    float x, y, z;
};


class Mesh {
public:
    unsigned int VAO, VBO, EBO;
    int indicesCount;

    Mesh(std::vector<float>& vertices, std::vector<unsigned int>& indices);
    void draw();
};


Mesh::Mesh(std::vector<float>& vertices, std::vector<unsigned int>& indices)
{
    indicesCount = static_cast<int>(vertices.size() / 3);

    EBO = 0;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(
        GL_ARRAY_BUFFER,
        vertices.size() * sizeof(float),
        vertices.data(),
        GL_STATIC_DRAW
    );

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float),
        (void*)0
    );

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


void Mesh::draw()
{
    glBindVertexArray(VAO);

    glDrawArrays(
        GL_TRIANGLE_FAN,
        0,
        indicesCount
    );

    glBindVertexArray(0);
}


class Transform {
public:
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
};


class Object {
public:
    Mesh* mesh;
    Transform transform;

    virtual void update(float deltaTime) {}
    virtual void draw() {};
};

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

const char* vertexShaderSource = R"(
#version 330 core

layout (location = 0) in vec3 aPos;

void main()
{
    gl_Position = vec4(aPos, 1.0);
}
)";

const char* fragmentShaderSource = R"(
#version 330 core

out vec4 FragColor;

void main()
{
    FragColor = vec4(0.85, 0.65, 0.20, 1.0);
}
)";

unsigned int compileShader(unsigned int type, const char* source)
{
    unsigned int shader = glCreateShader(type);

    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        std::cerr << "Blad kompilacji shadera:\n" << infoLog << std::endl;
    }

    return shader;
}

unsigned int createShaderProgram()
{
    unsigned int vertexShader = compileShader(GL_VERTEX_SHADER, vertexShaderSource);
    unsigned int fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);

    unsigned int shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if (!success)
    {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cerr << "Blad linkowania shaderow:\n" << infoLog << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}

std::vector<float> createGearVertices(
    Vec3 center,
    int teethCount,
    float innerRadius,
    float outerRadius
)
{
    std::vector<float> vertices;

    // œrodek ko³a
    vertices.push_back(center.x);
    vertices.push_back(center.y);
    vertices.push_back(center.z);

    int pointsCount = teethCount * 2;

    for (int i = 0; i < pointsCount + 1; i++) {
        float angle = (2.0f * PI * i) / pointsCount;

        float radius;

        if ((i / 2) % 2 == 0) {
            radius = outerRadius;
        }
        else {
            radius = innerRadius;
        }

        float x = center.x + radius * cos(angle);
        float y = center.y + radius * sin(angle);
        float z = center.z + 0.0f;

        vertices.push_back(x);
        vertices.push_back(y);
        vertices.push_back(z);
    }

    return vertices;
}

int main()
{
    Vec3 center1 = { -0.4f, 0.0f, 0.0f };
    Vec3 center2 = { 0.4f, 0.0f, 0.0f };

    std::vector<float> gearVertices1 = createGearVertices(center1, 20, 0.15f, 0.3f);
    std::vector<float> gearVertices2 = createGearVertices(center2, 20, 0.15f, 0.3f);

    std::vector<unsigned int> gearIndices1;
    std::vector<unsigned int> gearIndices2;

    if (!glfwInit())
    {
        std::cerr << "Nie udalo sie zainicjalizowac GLFW\n";
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Zegar 3D", nullptr, nullptr);

    if (!window)
    {
        std::cerr << "Nie udalo sie utworzyc okna GLFW\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Nie udalo sie zainicjalizowac GLAD\n";
        glfwDestroyWindow(window);
        glfwTerminate();
        return -1;
    }

    glViewport(0, 0, 800, 600);

    unsigned int shaderProgram = createShaderProgram();

    Gear gear1(gearVertices1, gearIndices1, 1.0f);
    Gear gear2(gearVertices2, gearIndices2, -1.0f);

    float lastTime = static_cast<float>(glfwGetTime());

    while (!glfwWindowShouldClose(window))
    {
        float currentTime = static_cast<float>(glfwGetTime());
        float deltaTime = currentTime - lastTime;
        lastTime = currentTime;

        glClearColor(0.1f, 1.0f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);

        gear1.update(deltaTime);
        gear2.update(deltaTime);

        gear1.draw();
        gear2.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}