#include "MeshImporter.h"
#include <span>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <ranges>

#include "DebugOutput.h"


std::optional<Mesh> MeshImporter::importFile(const std::string& pFile) {
    Mesh mesh;

    return mesh;
}
