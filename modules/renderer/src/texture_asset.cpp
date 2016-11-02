#include "ge/texture_asset.hpp"

namespace ge
{
std::shared_ptr<texture> texture_asset::load_asset(asset_manager& manager,
	const std::string& arg_name, const std::string& abs_filepath, const nlohmann::json& json_data)
{
	using namespace std::string_literals;

	std::string type_str = json_data["type"];
	type type_to_load;
	if (type_str == "DDS") {
		type_to_load = type::DDS;
	} else if (type_str == "PNG") {
		type_to_load = type::PNG;
	} else {
		logger->error("Unrecognized texture type found when loading texture_asset: " + type_str);
		return nullptr;
	}

	std::string filepath = json_data["file"];

	switch (type_to_load) {
	case type::DDS: {
		// just load file and sent it to the texture
		std::ifstream ifs{boost::filesystem::absolute(filepath, abs_filepath).string()};
		std::string dds_data(
			(std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

		auto ret = std::make_shared<texture>((const unsigned char*)dds_data.data(), arg_name);
		// check ret
		if (!*ret) return nullptr;
		return ret;
	} break;
	case type::PNG: {
		// use lodepng then pass the raw RGBA data

		std::vector<unsigned char> image_raw_data;
		glm::uvec2 size;

		auto path = boost::filesystem::absolute(filepath.c_str(), abs_filepath);

// make sure the file exists
#ifndef _NDEBUG
		if (!boost::filesystem::is_regular_file(path)) {
			logger->error(
				path.string() +
				" is not a valid path to a file. Error occured while loading texture asset \"" +
				arg_name + "\".");
		}
#endif

		auto ec = lodepng::decode(image_raw_data, size.x, size.y, path.string(), LCT_RGBA, 8);
		if (ec == 0) {
			logger->error("Failed lode PNG file with lodepng error: "s + lodepng_error_text(ec) +
						  std::to_string(ec));
		}

		auto ret = std::make_shared<texture>(image_raw_data.data(), size, arg_name);
		// check ret
		if (!*ret) return nullptr;
		return ret;
	}
	}
	return nullptr;
}
}
