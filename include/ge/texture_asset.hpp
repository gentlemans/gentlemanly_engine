#pragma once

#include "ge/concept/asset.hpp"
#include "ge/asset_manager.hpp"
#include "ge/texture.hpp"

#include "ge/lodepng.h"
#include "ge/json.hpp"

#include <string>
#include <stdexcept>
#include <iterator>

/*
 * ASSET SPEC:
 *
 * {
 *   "asset_type": "texture",
 *   "type": "DDS|PNG",
 *   "file": "/path/to/image/"
 * }
 *
 */

namespace ge
{
struct texture_asset
{
	std::shared_ptr<texture> data;

	enum class type
	{
		DDS,
		PNG
	};

	texture_asset(asset_manager& manager, const std::string& arg_name,
		const std::string& abs_filepath, const nlohmann::json& json_data)
	{
		std::string type_str = json_data["type"];
		type type_to_load;
		if (type_str == "DDS")
		{
			type_to_load = type::DDS;
		}
		else if (type_str == "PNG")
		{
			type_to_load = type::PNG;
		}
		else
		{
			throw std::runtime_error(
				"Unrecognized texture type found when loading texture_asset: " + type_str);
		}

		std::string filepath = json_data["file"];

		switch (type_to_load)
		{
			case type::DDS:
			{
				// just load file and sent it to the texture
				std::ifstream ifs{boost::filesystem::absolute(filepath, abs_filepath).string()};
				std::string dds_data(
					(std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));

				data = std::make_shared<texture>((const unsigned char*)dds_data.data());
			}
			break;
			case type::PNG:
			{
				// use lodepng then pass the raw RGBA data

				std::vector<unsigned char> image_raw_data;
				glm::uvec2 size;

				lodepng::decode(image_raw_data, size.x, size.y, boost::filesystem::absolute(filepath.c_str(), abs_filepath).c_str(), LCT_RGBA, 8);

				data = std::make_shared<texture>(image_raw_data.data(), size);
			}
		}
	}

	static const char* asset_type() { return "texture"; }
};
}
