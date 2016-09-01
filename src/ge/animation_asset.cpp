#include "ge/animation_asset.hpp"
#include "ge/texture.hpp"

#include "boost/filesystem.hpp"

namespace ge
{

std::shared_ptr<material> animation_asset::load_asset(
	asset_manager& manager, const char* name, const char* filepath, const nlohmann::json& json_data)
{
	namespace fs = boost::filesystem;

	float fps = json_data["fps"];
	int tiles_across = json_data["tiles_across"];

	std::string source_base_path = json_data["source_base_path"];

	auto abs_path = fs::absolute(source_base_path, filepath);

	// find the source files

	// get the base path
	auto base_dir = abs_path.parent_path();
	auto base_name = abs_path.filename().string();

	std::vector<fs::path> sources;

	for (fs::directory_entry& dir_entry : fs::directory_iterator(base_dir)) {
		if (dir_entry.path().parent_path().string().substr(0, base_name.length()) == base_name) {
			sources.emplace_back(dir_entry.path());
		}
	}

	// sort it
	std::sort(sources.begin(), sources.end());

	// generate the textures
	std::vector<std::shared_ptr<texture>> textures;

	for (auto& path : sources) {
		if (path.extension() == "dds" || path.extension() == "DDS") {
			// add it as a DDS file
		}
	}
	// TODO: fix
	return nullptr;
}
}
