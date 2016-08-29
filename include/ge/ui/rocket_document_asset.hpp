#ifndef GE_ROCKET_DOCUMENT_ASSET_HPP
#define GE_ROCKET_DOCUMENT_ASSET_HPP

#pragma once

#include "ge/concept/asset.hpp"

#include <Rocket/Core/Context.h>
#include <Rocket/Core/ElementDocument.h>

#include <memory>

#include "ge/json.hpp"

/*
 * ASSET SPECIFICATION
 *
 * {
 *   "type": "rocket_document",
 *   "rml_file": "path/to/rml/file(defaults to doc.rml)"
 *   "required_fonts": [
 *     "font1",
 *     "font2"
 *   ] (optional)
 * }
 *
 */

namespace ge
{
namespace ui
{
struct rocket_document_asset {
	using loaded_type = Rocket::Core::ElementDocument;

	static std::shared_ptr<loaded_type> load_asset(asset_manager& manager, const char* asset_name,
		const char* filepath, const nlohmann::json& json_data, Rocket::Core::Context* ctx);

	static const char* asset_type() { return "rocket_document"; }
};
BOOST_CONCEPT_ASSERT((concept::Asset<rocket_document_asset>));
}
}

#endif // GE_ROCKET_DOCUMENT_ASSET_HPP
