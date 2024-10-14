#pragma once
#include <string>
#include <optional>
#include "Model.h"

class MeshImporter
{
public:
    static std::optional<Model> importFile(const std::string& pFile);
};
