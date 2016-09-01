#ifndef GE_ANIMATION_ASSET_HPP
#define GE_ANIMATION_ASSET_HPP

#pragma once

#include "ge/asset_manager.hpp"
#include "ge/material.hpp"

/* ASSET SPECIFICATION:
 *
 * {
 *   "type": "animation",
 *   "fps": "frames per second",
 *   "tiles_across": "how many tiles across in each image. For example, an image with 25 tiles would
 * have 5 tiles across",
 *   "source_base_path": "the base path of the files, to be appended with a number."
 * }
 */

namespace ge
{
struct animation_asset {
	using loaded_type = material;

	static std::shared_ptr<material> load_asset(asset_manager& manager, const char* name,
		const char* filepath, const nlohmann::json& json_data);

	static const char* asset_type() { return "animation"; }
};
}

#endif  // GE_ANIMATION_ASSET_HPP
