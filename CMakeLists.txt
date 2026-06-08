cmake_minimum_required(VERSION 3.20)

project(Clock3D)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Clock3D
    src/main.cpp
)

find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(OpenGL REQUIRED)

target_link_libraries(Clock3D PRIVATE
    glfw
    glad::glad
    glm::glm
    OpenGL::GL
)