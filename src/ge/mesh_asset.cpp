#include "ge/mesh_asset.hpp"
#include "ge/material_asset.hpp"

#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>

#include <boost/filesystem.hpp>

namespace ge
{
mesh_asset::mesh_asset(asset_manager& manager, const std::string& arg_name,
	const std::string& abs_filepath, const nlohmann::json& json_data)
{
	std::string path;
	if (json_data["obj_data"].is_string())
	{
		path = json_data["obj_data"];
	}
	else
	{
		path = "object.obj";
	}

	path = boost::filesystem::absolute(path, abs_filepath).string();

	Assimp::Importer importer;
	const aiScene* scene =
		importer.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
	if (!scene)
	{
		throw std::runtime_error(
			"Failed to import file: " + path + " Reason: " + importer.GetErrorString());
	}
	if (!scene->HasMeshes())
	{
		throw std::runtime_error("Failed to import file: " + path + " Reason: no meshes");
	}

	auto& mesh_ref = *scene->mMeshes[0];

	std::vector<float> locs(mesh_ref.mNumVertices * 3);
	memcpy(locs.data(), mesh_ref.mVertices, sizeof(aiVector3D) * mesh_ref.mNumVertices);

	// remove Z's, this is a 2D engine
	for (size_t index = 2; index < locs.size(); index += 2)
	{
		locs.erase(locs.begin() + index);
	}

	// build element vector
	std::vector<glm::uvec3> elements(mesh_ref.mNumFaces * 3);
	for (auto index_of_face = 0; index_of_face < mesh_ref.mNumFaces; ++index_of_face)
	{
		elements[index_of_face] = {
			mesh_ref.mFaces[index_of_face].mIndices[0], mesh_ref.mFaces[index_of_face].mIndices[1],
			mesh_ref.mFaces[index_of_face].mIndices[2],
		};
	}

	// these reinterpret_casts are safe because glm makes sure to not have any
	// padding
	data = std::make_shared<mesh>(reinterpret_cast<glm::vec2*>(locs.data()),
		reinterpret_cast<glm::vec2*>(mesh_ref.mTextureCoords), locs.size(), elements.data(),
		mesh_ref.mNumFaces);

	// load up material
	std::string material_asset_path = json_data["material"];
	auto mat = manager.get_asset<material_asset>(material_asset_path.c_str());

	data->m_material = std::move(mat.data);
}
}
