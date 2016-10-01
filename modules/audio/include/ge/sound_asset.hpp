#ifndef GE_SOUND_ASSET_HPP
#define GE_SOUND_ASSET_HPP

#pragma once

#include "ge/asset_manager.hpp"
#include "ge/sound.hpp"

#include <memory>

namespace ge
{
/// Loader for sound files
struct sound_asset {
	using loaded_type = sound;
	using cached = std::true_type;

	static std::shared_ptr<sound> load_asset(asset_manager& manager, const char* name,
		const char* filepath, const nlohmann::json& json_data);
};
}

#endif  // GE_SOUND_ASSET_HPP
