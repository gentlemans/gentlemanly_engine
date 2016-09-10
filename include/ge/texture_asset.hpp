#ifndef GE_TEXTURE_ASSET_HPP
#define GE_TEXTURE_ASSET_HPP

#pragma once

#include "ge/asset_manager.hpp"
#include "ge/concept/asset.hpp"
#include "ge/texture.hpp"

#include "ge/json.hpp"
#include "ge/lodepng.h"

#include <iterator>
#include <stdexcept>
#include <string>

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
struct texture_asset {
	enum class type { DDS, PNG };

	using loaded_type = texture;
	using cached = std::true_type;

	static std::shared_ptr<texture> load_asset(asset_manager& manager, const std::string& arg_name,
		const std::string& abs_filepath, const nlohmann::json& json_data);

	static const char* asset_type() { return "texture"; }
};
}

#endif  // GE_TEXTURE_ASSET_HPP
