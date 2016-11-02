#ifndef GE_SHADER_ASSET_HPP
#define GE_SHADER_ASSET_HPP

#pragma once

#include "ge/asset_manager.hpp"
#include "ge/concept/asset.hpp"
#include "ge/shader.hpp"
#include "ge/texture_asset.hpp"

#include "ge/json.hpp"
#include "ge/json_helper.hpp"

#include <string>

#include <boost/filesystem.hpp>
#include <boost/variant.hpp>

namespace ge
{
/// A shader_asset loads a shader, and exposes properties to this shader, to be set in a material.
/// [asset.json
/// Specification](https://lbovet.github.io/docson/index.html#https://raw.githubusercontent.com/gentlemans/gentlemanly_engine/master/doc/json_spec/shader_asset.json)
class shader_asset
{
public:
	/// Loads shader objects
	using loaded_type = shader;

	/// Asset loading function
	static std::shared_ptr<shader> load_asset(asset_manager& manager, const std::string& arg_name,
		const std::string& abs_filepath, const nlohmann::json& json_data);

	/// Require assets to have "asset_type": "shader"
	static const char* asset_type() { return "shader"; }
	
	// make sure it qualifies as an asset
	BOOST_CONCEPT_ASSERT((concept::Asset<shader_asset>));
};
}

#endif  // GE_SHADER_ASSET_HPP
