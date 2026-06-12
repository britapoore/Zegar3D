#pragma once

#include <vector>
#include <memory>
#include "ObjFactory.h"

void addObjects(std::vector<std::unique_ptr<Object>>& objects, unsigned int metalTex, unsigned int goldTex);