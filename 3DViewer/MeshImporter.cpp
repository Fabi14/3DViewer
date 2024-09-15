#include "MeshImporter.h"
#include <span>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <ranges>

#include "DebugOutput.h"

namespace
{
    glm::vec3 toVec3(const auto& v)
    {
        return { v.x,v.y,v.z };
    }
    glm::vec4 toVec4(const auto& v)
    {
        return { v.r,v.g,v.b,v.a };
    }
}

std::optional<Mesh> MeshImporter::DoTheImportThing(const std::string& pFile) {
    // Create an instance of the Importer class
    Assimp::Importer importer;

    // And have it read the given file with some example postprocessing
    // Usually - if speed is not the most important aspect for you - you'll
    // probably to request more postprocessing than we do in this example.
    const aiScene* pModel = importer.ReadFile(pFile,
  //      aiProcess_CalcTangentSpace |
        aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices |
        aiProcess_SortByPType);

    // If the import failed, report it
    if (!pModel) {
        DebugOutput::printDebugMessage(importer.GetErrorString());
        return std::nullopt;
    }

    const auto* pMesh = pModel->mMeshes[0];

    Mesh mesh;
    mesh.m_vertices.reserve(pMesh->mNumVertices);
    for (const auto [i, vertex] : std::views::enumerate(std::span{ pMesh->mVertices, pMesh->mNumVertices }))
    {
        mesh.m_vertices.push_back({ .pos = toVec3(vertex),
                                    .col = glm::vec4{0.2f,0.2f,0.2f,1.f},
                                    .normal = toVec3(pMesh->mNormals[i])});
    }

    for (const auto face : std::span{ pMesh->mFaces, pMesh->mNumFaces })
    {
        assert(face.mNumIndices == 3);
        mesh.m_indices.insert_range(mesh.m_indices.end(), std::span{ face.mIndices,3 });
    }

    return mesh;
}
