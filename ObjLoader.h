#pragma once
#include <string>
#include "Types.h"

class ObjLoader
{
public:
    static ObjData load(const std::string& path, float scale);

private:
    static unsigned int parseObjIndex(const std::string& token);
};