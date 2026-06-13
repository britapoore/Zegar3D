#include <iostream>
#include <fstream>
#include <limits>
#include <sstream>
#include <vector>
#include <map>

#include "ObjLoader.h"

unsigned int ObjLoader::parseObjIndex(const std::string& token)
{
    std::string number = token;
    size_t slashPos = token.find('/');
    if (slashPos != std::string::npos) number = token.substr(0, slashPos);
    return static_cast<unsigned int>(std::stoi(number) - 1);
}

void parseToken(const std::string& token, unsigned int& vIdx, unsigned int& nIdx) {
    std::stringstream ss(token);
    std::string vStr, tStr, nStr;
    std::getline(ss, vStr, '/');
    std::getline(ss, tStr, '/');
    std::getline(ss, nStr, '/');
    vIdx = std::stoi(vStr) - 1;
    if (!nStr.empty()) nIdx = std::stoi(nStr) - 1;
    else nIdx = 0; // domyślna
}

ObjData ObjLoader::load(const std::string& path, float scale)
{
    ObjData data;
    Vec3 minVertex = { std::numeric_limits<float>::max(), std::numeric_limits<float>::max(), std::numeric_limits<float>::max() };
    Vec3 maxVertex = { std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest(), std::numeric_limits<float>::lowest() };

    std::ifstream file(path);
    if (!file.is_open())
    {
        std::cerr << "Nie udalo sie otworzyc pliku OBJ: " << path << std::endl;
        return data;
    }

    std::vector<Vec3> temp_vertices;
    std::vector<Vec3> temp_normals;
    std::map<std::string, unsigned int> uniqueVertices;
    unsigned int nextIndex = 0;

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
            vertex.x *= scale; vertex.y *= scale; vertex.z *= scale;
            temp_vertices.push_back(vertex);

            minVertex.x = std::min(minVertex.x, vertex.x);
            minVertex.y = std::min(minVertex.y, vertex.y);
            minVertex.z = std::min(minVertex.z, vertex.z);
            maxVertex.x = std::max(maxVertex.x, vertex.x);
            maxVertex.y = std::max(maxVertex.y, vertex.y);
            maxVertex.z = std::max(maxVertex.z, vertex.z);
        }
        else if (type == "vn")
        {
            Vec3 normal;
            ss >> normal.x >> normal.y >> normal.z;
            temp_normals.push_back(normal);
        }
        else if (type == "f")
        {
            std::vector<unsigned int> faceIndices;
            std::string token;

            while (ss >> token)
            {
                if (uniqueVertices.count(token) == 0) {
                    uniqueVertices[token] = nextIndex;
                    unsigned int vIdx = 0, nIdx = 0;
                    parseToken(token, vIdx, nIdx);
                    
                    Vec3 v = temp_vertices[vIdx];
                    Vec3 n = {0.0f, 0.0f, 0.0f};
                    if (nIdx < temp_normals.size()) n = temp_normals[nIdx];
                    
                    data.vertices.push_back(v.x);
                    data.vertices.push_back(v.y);
                    data.vertices.push_back(v.z);
                    data.vertices.push_back(n.x);
                    data.vertices.push_back(n.y);
                    data.vertices.push_back(n.z);
                    
                    nextIndex++;
                }
                faceIndices.push_back(uniqueVertices[token]);
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

    if (!temp_vertices.empty())
    {
        data.center = {
            (minVertex.x + maxVertex.x) * 0.5f,
            (minVertex.y + maxVertex.y) * 0.5f,
            (minVertex.z + maxVertex.z) * 0.5f
        };
    }

    std::cout << "Wczytano OBJ: " << path << std::endl;
    std::cout << "Liczba unikalnych wierzcholkow: " << nextIndex << std::endl;
    std::cout << "Liczba indeksow: " << data.indices.size() << std::endl;

    return data;
}
