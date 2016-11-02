#ifndef GE_ROCKET_DOCUMENT_ASSET_HPP
#define GE_ROCKET_DOCUMENT_ASSET_HPP

#pragma once

#include "ge/concept/asset.hpp"

#include <Rocket/Core/Context.h>
#include <Rocket/Core/ElementDocument.h>

#include <memory>

#include "ge/json.hpp"

namespace ge
{
/// A asset loader for rocket documents
/// [asset.json
/// specification](https://lbovet.github.io/docson/index.html#https://raw.githubusercontent.com/gentlemans/gentlemanly_engine/master/doc/json_spec/rocket_document_asset.json)
struct rocket_document_asset {
	/// Load a ElementDocument
	using loaded_type = Rocket::Core::ElementDocument;

	/// Asset loader function
	static std::shared_ptr<loaded_type> load_asset(asset_manager& manager, const char* asset_name,
		const char* filepath, const nlohmann::json& json_data);

	/// Require the asset to have "asset_type": "rocket_document"
	static const char* asset_type() { return "rocket_document"; }
	
	// make sure it qualifies as an asset
	BOOST_CONCEPT_ASSERT((concept::Asset<rocket_document_asset>));
};
}

#endif  // GE_ROCKET_DOCUMENT_ASSET_HPP
