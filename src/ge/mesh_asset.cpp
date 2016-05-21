#include "ge/mesh_asset.hpp"
#include "ge/material_asset.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


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
	const aiScene* scene = importer.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);
	if(!scene) {
		throw std::runtime_error("Failed to import file: " + path + " Reason: " + importer.GetErrorString());
	}
	if(!scene->HasMeshes()) {
		throw std::runtime_error("Failed to import file: " + path + " Reason: no meshes");
	}
	std::vector<float> locs(scene->mMeshes[0]->mNumVertices * 3);
	memcpy(locs.data(), scene->mMeshes[0]->mVertices, sizeof(aiVector2D) * scene->mMeshes[0]->mNumVertices);
	
	// remove Z's, this is a 2D engine
	for (size_t index = 2; index < locs.size(); index += 2)
	{
		locs.erase(locs.begin() + index);
	}

	// these reinterpret_casts are safe because glm makes sure to not have any
	// padding
	data = std::make_shared<mesh>(reinterpret_cast<glm::vec2*>(locs.data()),
		reinterpret_cast<glm::vec2*>(locs.data()), 
		locs.size(),
		reinterpret_cast<glm::uvec3*>(scene->mMeshes[0]->mFaces), 
		scene->mMeshes[0]->mNumFaces);

	// load up material
	std::string material_asset_path = json_data["material"];
	auto mat = manager.get_asset<material_asset>(material_asset_path.c_str());

	data->m_material = std::move(mat.data);
}
}
