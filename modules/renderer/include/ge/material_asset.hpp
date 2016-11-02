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
/// [asset.json
/// specification](https://lbovet.github.io/docson/index.html#https://raw.githubusercontent.com/gentlemans/gentlemanly_engine/master/doc/json_spec/material_asset.json)
class material_asset
{
public:
	/// Load a material
	using loaded_type = material;

	/// Asset loadeer
	static std::shared_ptr<material> load_asset(asset_manager& manager, const char* name,
		const char* filepath, const nlohmann::json& json_data);

	/// Require the asset to have "asset_type": "material"
	static const char* asset_type() { return "material"; }
};

BOOST_CONCEPT_ASSERT((concept::Asset<material_asset>));
}

#endif  // GE_MATERIAL_ASSET_HPP
