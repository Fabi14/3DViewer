#pragma once
#include <string>
#include <optional>
#include "Mesh.h"

class MeshImporter
{
public:
    static std::optional<Mesh> importFile(const std::string& pFile);
};

