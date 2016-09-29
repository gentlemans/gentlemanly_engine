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

namespace ge
{
/// A asset loader for textures
///
/// ASSET SPECIFICATION:
/// ```
/// {
///   "asset_type": "texture",
///   "type": "DDS|PNG",
///   "file": "/path/to/image/"
/// }
/// ```
struct texture_asset {
private:
	enum class type { DDS, PNG };

public:
	/// Loads textures
	using loaded_type = texture;

	/// With cacheing
	using cached = std::true_type;

	/// Asset loading function
	static std::shared_ptr<texture> load_asset(asset_manager& manager, const std::string& arg_name,
		const std::string& abs_filepath, const nlohmann::json& json_data);

	/// Require the asset to have "asset_type": "texture"
	static const char* asset_type() { return "texture"; }
};
}

#endif  // GE_TEXTURE_ASSET_HPP
