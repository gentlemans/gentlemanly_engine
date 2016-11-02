#ifndef GE_SOUND_ASSET_HPP
#define GE_SOUND_ASSET_HPP

#pragma once

#include "ge/asset_manager.hpp"
#include "ge/sound.hpp"

#include <memory>

namespace ge
{
/// Loader for sound files
/// [asset.json
/// specification](https://lbovet.github.io/docson/index.html#https://raw.githubusercontent.com/gentlemans/gentlemanly_engine/master/doc/json_spec/sound_asset.json)
struct sound_asset {
	/// It loads sounds
	using loaded_type = sound;

	/// Load asset function. (see asset.md)
	/// \param manager The asset manager
	/// \param name The name of the asset
	/// \param filepath The path to the asset directory
	/// \param json_data The JSON loaded from asset.json
	/// \return The loaded sound
	static std::shared_ptr<sound> load_asset(asset_manager& manager, const char* name,
		const char* filepath, const nlohmann::json& json_data);

	/// Tell the asset_manager that asset.json files should be marked with "sound"
	/// \return "sound"
	static const char* asset_type() { return "sound"; }
	
	// make sure it qualifies as an asset
	BOOST_CONCEPT_ASSERT((concept::Asset<sound_asset>));
};
}

#endif  // GE_SOUND_ASSET_HPP
