#include "ge/mesh_asset.hpp"
#include "ge/material_asset.hpp"

#include "ge/tiny_obj_loader.h"

#include <boost/filesystem.hpp>

namespace ge
{
std::shared_ptr<mesh> mesh_asset::load_asset(asset_manager& manager, const std::string& arg_name,
	const std::string& abs_filepath, const nlohmann::json& json_data)
{
	std::string path;
	if (json_data["obj_data"].is_string()) {
		path = json_data["obj_data"];
	} else {
		path = "object.obj";
	}

	path = boost::filesystem::absolute(path, abs_filepath).string();

	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string err;

	bool success =
		tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path.c_str(), nullptr, true);

	if (!success) {
		log->error("Failed to import file: " + path + " Reason: " + err);
		return nullptr;
	}
	if (shapes.size() == 0) {
		log->error("Failed to import file: " + path + " Reason: no meshes");
		return nullptr;
	}

	auto& mesh_ref = shapes[0].mesh;

	std::vector<glm::vec2> locs;
	locs.reserve(mesh_ref.num_face_vertices.size() * 3);  // they are all tris

	std::vector<glm::uvec3> elements;
	elements.reserve(mesh_ref.indices.size() / 3);

	// create locs from attrib, tossing out Z
	for (auto vidx = 0ull; vidx < attrib.vertices.size(); vidx += 3) {
		locs.emplace_back(attrib.vertices[vidx], attrib.vertices[vidx + 1]);
	}

	// texcoords are the same, just memcpy those--glm's vector types are garunteed to have no
	// padding
	std::vector<glm::vec2> texcoords;
	texcoords.resize(attrib.texcoords.size() / 2);
	memcpy(texcoords.data(), attrib.texcoords.data(), sizeof(float) * attrib.texcoords.size());

	// create elements from the faces
	for (auto faceid = 0ull; faceid < mesh_ref.num_face_vertices.size(); ++faceid) {
		assert(mesh_ref.num_face_vertices[faceid] ==
			   3);  // shoudln't ever fail, triangulate is turned on

		auto v1idx = mesh_ref.indices[faceid * 3];
		auto v2idx = mesh_ref.indices[faceid * 3 + 1];
		auto v3idx = mesh_ref.indices[faceid * 3 + 2];

		elements.emplace_back(v1idx.vertex_index, v2idx.vertex_index, v3idx.vertex_index);
	}

	// these reinterpret_casts are safe because glm makes sure to not have any
	// padding
	auto ret = std::make_shared<mesh>(reinterpret_cast<glm::vec2*>(locs.data()), locs.size(),
		elements.data(), mesh_ref.num_face_vertices.size());

	ret->add_additional_data("uv", texcoords.data(), texcoords.size() * sizeof(glm::vec2));

	return ret;
}
}
