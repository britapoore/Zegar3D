#include <iostream>
#include <fstream>
#include <limits>
#include <sstream>
#include <vector>

#include "ObjLoader.h"


unsigned int ObjLoader::parseObjIndex(const std::string& token)
{
    std::string number = token;

    size_t slashPos = token.find('/');
    if (slashPos != std::string::npos)
    {
        number = token.substr(0, slashPos);
    }

    return static_cast<unsigned int>(std::stoi(number) - 1);
}

ObjData ObjLoader::load(const std::string& path, float scale)
{
    ObjData data;
    Vec3 minVertex = {
        std::numeric_limits<float>::max(),
        std::numeric_limits<float>::max(),
        std::numeric_limits<float>::max()
    };
    Vec3 maxVertex = {
        std::numeric_limits<float>::lowest(),
        std::numeric_limits<float>::lowest(),
        std::numeric_limits<float>::lowest()
    };

    std::ifstream file(path);

    if (!file.is_open())
    {
        std::cerr << "Nie udalo sie otworzyc pliku OBJ: " << path << std::endl;
        return data;
    }

    std::string line;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);

        std::string type;
        ss >> type;

        if (type == "v")
        {
            Vec3 vertex;
            ss >> vertex.x >> vertex.y >> vertex.z;

            vertex.x *= scale;
            vertex.y *= scale;
            vertex.z *= scale;

            data.vertices.push_back(vertex.x);
            data.vertices.push_back(vertex.y);
            data.vertices.push_back(vertex.z);

            minVertex.x = std::min(minVertex.x, vertex.x);
            minVertex.y = std::min(minVertex.y, vertex.y);
            minVertex.z = std::min(minVertex.z, vertex.z);
            maxVertex.x = std::max(maxVertex.x, vertex.x);
            maxVertex.y = std::max(maxVertex.y, vertex.y);
            maxVertex.z = std::max(maxVertex.z, vertex.z);
        }
        else if (type == "f")
        {
            std::vector<unsigned int> faceIndices;
            std::string token;

            while (ss >> token)
            {
                faceIndices.push_back(parseObjIndex(token));
            }

            for (int i = 1; i < static_cast<int>(faceIndices.size()) - 1; i++)
            {
                data.indices.push_back(faceIndices[0]);
                data.indices.push_back(faceIndices[i]);
                data.indices.push_back(faceIndices[i + 1]);
            }
        }
    }

    file.close();

    if (!data.vertices.empty())
    {
        data.center = {
            (minVertex.x + maxVertex.x) * 0.5f,
            (minVertex.y + maxVertex.y) * 0.5f,
            (minVertex.z + maxVertex.z) * 0.5f
        };
    }

    std::cout << "Wczytano OBJ: " << path << std::endl;
    std::cout << "Liczba wierzcholkow: " << data.vertices.size() / 3 << std::endl;
    std::cout << "Liczba indeksow: " << data.indices.size() << std::endl;

    return data;
}
