#include "ge/mesh_asset.hpp"

#include <tiny_obj_loader.h>

#include <boost/filesystem.hpp>

namespace ge
{
mesh_asset::mesh_asset(asset_manager& manager, const std::string& arg_name,
	const std::string& abs_filepath, const Json::Value& json_data)
{
	auto path = json_data.get("obj_data", "mesh.obj").asString();
	path = boost::filesystem::absolute(path, abs_filepath).string();

	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	std::string err;
	tinyobj::LoadObj(shapes, materials, err, path.c_str());

	if (shapes.size() == 0) throw std::runtime_error("Error: No shapes in OBJ. Error: " + err);

	auto& mesh_ref = shapes[0].mesh;

	// remove Z's, this is a 2D engine
	for (size_t index = 2; index < mesh_ref.positions.size(); index += 2)
	{
		mesh_ref.positions.erase(mesh_ref.positions.begin() + index);
	}

	// these reinterpret_casts are safe because glm makes sure to not have any
	// padding
	data = std::make_shared<mesh>(reinterpret_cast<glm::vec2*>(mesh_ref.positions.data()),
		reinterpret_cast<glm::vec2*>(mesh_ref.texcoords.data()), mesh_ref.positions.size() / 2,
		reinterpret_cast<glm::uvec3*>(mesh_ref.indices.data()), mesh_ref.indices.size() / 3);
}
}
