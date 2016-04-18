#pragma once

#include "ge/material.hpp"
#include "ge/asset_manager.hpp"

#include "ge/json/json.h"

#include <memory>
#include <string>
#include <vector>

/*
 * Asset Spec
 *
 * {
 *   "asset_type": "material",
 *   "shader": "/asset/name/for/shader",
 *
 * }
 *
 */

namespace ge
{
class material_asset
{
public:
	std::shared_ptr<material> data;

	material_asset(asset_manager& manager, const char* name, const char* filepath,
		const Json::Value& json_data);

	static const char* asset_type() { return "material"; }
};

BOOST_CONCEPT_ASSERT((concept::Asset<material_asset>));
}
