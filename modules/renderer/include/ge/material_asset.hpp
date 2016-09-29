#ifndef GE_MATERIAL_ASSET_HPP
#define GE_MATERIAL_ASSET_HPP

#pragma once

#include "ge/asset_manager.hpp"
#include "ge/material.hpp"

#include "ge/json.hpp"

#include <memory>
#include <string>
#include <vector>

namespace ge
{
/// A material asset loader
///
/// ```
/// {
///   "asset_type": "material",
///   "shader": "/path/to/shader_asset",
///   "parameters": [
///     {
///       "name": "the name of the shader",
///       "value": "The value, use JSON arrays for vectors and path to a texture for texture"
///     }
///   ]
///  }
/// ```
class material_asset
{
public:
	/// Load a material
	using loaded_type = material;

	/// And don't cache it, materials need to be mutable
	using cached = std::false_type;

	/// Asset loadeer
	static material load_asset(asset_manager& manager, const char* name, const char* filepath,
		const nlohmann::json& json_data);

	/// Require the asset to have "asset_type": "material"
	static const char* asset_type() { return "material"; }
};

BOOST_CONCEPT_ASSERT((concept::Asset<material_asset>));
}

#endif  // GE_MATERIAL_ASSET_HPP
