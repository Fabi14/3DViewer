#include "MeshImporter.h"
#include <span>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <ranges>

#include "DebugOutput.h"
#include "Mesh.h"

#define GLM_ENABLE_EXPERIMENTAL
#include<glm/gtx/transform.hpp>

namespace
{
    glm::vec2 toVec2(const auto& v)
    {
        return { v.x,v.y };
    }
    glm::vec3 toVec3(const auto& v)
    {
        return { v.x,v.y,v.z };
    }
    glm::vec4 toVec4(const auto& v)
    {
        return { v.r,v.g,v.b,v.a };
    }

    glm::mat4 convertMatrix(const aiMatrix4x4& mat)
    {
        return glm::transpose(glm::mat4{ mat.a1, mat.a2, mat.a3, mat.a4,
                            mat.b1, mat.b2, mat.b3, mat.b4,
                            mat.c1, mat.c2, mat.c3, mat.c4,
                            mat.d1, mat.d2, mat.d3, mat.d4 });
    }

    Mesh convertMesh(const aiMesh* pMesh)
    {
        Mesh mesh;
        mesh.m_vertices.reserve(pMesh->mNumVertices);
        for (const auto&& [i, vertex] : std::views::enumerate(std::span{ pMesh->mVertices, pMesh->mNumVertices }))
        {
            glm::vec2 uv{};
            if (pMesh->GetNumUVChannels() >= 1 && pMesh->HasTextureCoords(0))
            {
                uv = toVec2(pMesh->mTextureCoords[0][i]);
            }

            mesh.m_vertices.push_back(
                { .pos = toVec3(vertex),
                       .col = glm::vec4{1.0f,0.0f,0.0f,1.f},
                       .normal = toVec3(pMesh->mNormals[i]),
                        .uvs = uv
                });
        }

        for (const auto face : std::span{ pMesh->mFaces, pMesh->mNumFaces })
        {
            assert(face.mNumIndices == 3);
            mesh.m_indices.insert_range(mesh.m_indices.end(), std::span{ face.mIndices,3 });
        }
        return mesh;
    }


    void convertNodes(aiNode* node, const aiScene* pScene, Model& model, glm::mat4 trans)
    {

        for (const auto& meshIdx : std::span{ node->mMeshes,node->mNumMeshes })
        {
            auto* pMesh = pScene->mMeshes[meshIdx];
            auto mesh{ convertMesh(pMesh) };


            model.m_vecRenderables.push_back(Renderable{
                .m_vertexBuffer = VertexBuffer{ mesh.m_vertices, mesh.m_indices},
                .m_modelTransform = trans * convertMatrix(node->mTransformation)  });
        }
        for (const auto& childNodes : std::span{ node->mChildren,node->mNumChildren })
        {
            convertNodes(childNodes, pScene, model, trans * convertMatrix(node->mTransformation) );
        }
    }
    Mesh getCubeMesh()
    {
        return Mesh{
            {
                //front
                {{-0.5f, -0.5f, 0.5f},	{0.0f,0.5f,0.1f,1.0f}, {0.0f, 0.0f, 1.0f},{0.f,0.f}},
                {{-0.5f,  0.5f, 0.5f},	{1.0f,0.5f,0.1f,1.0f}, {0.0f, 0.0f, 1.0f},{0.f,1.f}},
                {{ 0.5f,  0.5f, 0.5f},	{0.5f,0.5f,0.1f,1.0f}, {0.0f, 0.0f, 1.0f},{1.f,1.f}},
                {{ 0.5f, -0.5f, 0.5f},	{0.0f,0.5f,1.0f,1.0f}, {0.0f, 0.0f, 1.0f},{1.f,0.f}},

                //back	  
                {{ 0.5f, -0.5f,-0.5f},	{0.0f,0.5f,0.1f,1.0f}, {0.0f, 0.0f, -1.0f},{0.f,0.f}},
                {{ 0.5f,  0.5f,-0.5f},	{1.0f,0.5f,0.1f,1.0f}, {0.0f, 0.0f, -1.0f},{0.f,1.f}},
                {{-0.5f,  0.5f,-0.5f},	{0.5f,0.5f,0.1f,1.0f}, {0.0f, 0.0f, -1.0f},{1.f,1.f}},
                {{-0.5f, -0.5f,-0.5f},	{0.0f,0.5f,1.0f,1.0f}, {0.0f, 0.0f, -1.0f},{1.f,0.f}},

                //left
                {{-0.5f, -0.5f, -0.5f},	{0.0f,0.5f,0.1f,1.0f}, {-1.0f, 0.0f, 0.0f}, { 0.f,0.f }},
                {{-0.5f,  0.5f, -0.5f},	{1.0f,0.5f,0.1f,1.0f}, {-1.0f, 0.0f, 0.0f}, { 0.f,1.f }},
                {{-0.5f,  0.5f,  0.5f},	{0.5f,0.5f,0.1f,1.0f}, {-1.0f, 0.0f, 0.0f}, { 1.f,1.f }},
                {{-0.5f, -0.5f,  0.5f},	{0.0f,0.5f,1.0f,1.0f}, {-1.0f, 0.0f, 0.0f}, { 1.f,0.f }},

                //right
                {{0.5f, -0.5f,  0.5f},	{0.0f,0.5f,0.1f,1.0f}, {1.0f, 0.0f, 0.0f}, { 0.f,0.f }},
                {{0.5f,  0.5f,  0.5f},	{1.0f,0.5f,0.1f,1.0f}, {1.0f, 0.0f, 0.0f}, { 0.f,1.f }},
                {{0.5f,  0.5f, -0.5f},	{0.5f,0.5f,0.1f,1.0f}, {1.0f, 0.0f, 0.0f}, { 1.f,1.f }},
                {{0.5f, -0.5f, -0.5f},	{0.0f,0.5f,1.0f,1.0f}, {1.0f, 0.0f, 0.0f}, { 1.f,0.f }},

                //top
                {{-0.5f, 0.5f,  0.5f},	{0.0f,0.5f,0.1f,1.0f}, {0.0f, 1.0f, 0.0f}, { 0.f,0.f }},
                {{-0.5f, 0.5f, -0.5f},	{1.0f,0.5f,0.1f,1.0f}, {0.0f, 1.0f, 0.0f}, { 0.f,1.f }},
                {{ 0.5f, 0.5f, -0.5f},	{0.5f,0.5f,0.1f,1.0f}, {0.0f, 1.0f, 0.0f}, { 1.f,1.f }},
                {{ 0.5f, 0.5f,  0.5f},	{0.0f,0.5f,1.0f,1.0f}, {0.0f, 1.0f, 0.0f}, { 1.f,0.f }},

                //bottom
                {{-0.5f, -0.5f, -0.5f},	{0.0f,0.5f,0.1f,1.0f}, {0.0f, -1.0f, 0.0f}, { 0.f,0.f }},
                {{-0.5f, -0.5f,  0.5f},	{1.0f,0.5f,0.1f,1.0f}, {0.0f, -1.0f, 0.0f}, { 0.f,1.f }},
                {{ 0.5f, -0.5f,  0.5f},	{0.5f,0.5f,0.1f,1.0f}, {0.0f, -1.0f, 0.0f}, { 1.f,1.f }},
                {{ 0.5f, -0.5f, -0.5f},	{0.0f,0.5f,1.0f,1.0f}, {0.0f, -1.0f, 0.0f}, { 1.f,0.f }},
            },
            {

                0,3,2,0,2,1,
                0 + 4,3 + 4,2 + 4,0 + 4,2 + 4,1 + 4,
                0 + 8,3 + 8,2 + 8,0 + 8,2 + 8,1 + 8,
                0 + 12,3 + 12,2 + 12,0 + 12,2 + 12,1 + 12,
                0 + 16,3 + 16,2 + 16,0 + 16,2 + 16,1 + 16,
                0 + 20,3 + 20,2 + 20,0 + 20,2 + 20,1 + 20,
            }
        };
    }
}


std::optional<Model> MeshImporter::importFile(const std::string& pFile) {
    // Create an instance of the Importer class
    Assimp::Importer importer;

    // And have it read the given file with some example postprocessing
    // Usually - if speed is not the most important aspect for you - you'll
    // probably to request more postprocessing than we do in this example.
    const aiScene* pScene = importer.ReadFile(pFile,
  //      aiProcess_CalcTangentSpace |
        aiProcess_Triangulate |
        aiProcess_JoinIdenticalVertices |
        aiProcess_SortByPType);

    // If the import failed, report it
    if (!pScene) {
        DebugOutput::printDebugMessage(importer.GetErrorString());
        return std::nullopt;
    }

    Model model;
    convertNodes(pScene->mRootNode, pScene, model, glm::mat4{ 1.f });

    return model;
}

Model MeshImporter::getCube()
{
    using namespace std::views;
    Model model;

    auto inst = cartesian_product(
        iota(1,20), iota(1,20), iota(1,20)) 
        | transform([](auto ijk)->InstanceData 
            {
                const auto& [i, j, k] = ijk;
                return InstanceData(glm::translate(glm::mat4{ 1.f },{ i * 50.f,j * 55.f,k * 55.f }));
            });
    std::vector<InstanceData> instances(inst.begin(), inst.end());


    auto mesh{ getCubeMesh() };
    model.m_vecRenderables.push_back(Renderable{
                .m_vertexBuffer = VertexBuffer{ mesh.m_vertices, mesh.m_indices,instances},
                .m_modelTransform = glm::mat4{1.f} });
    return model;
}
