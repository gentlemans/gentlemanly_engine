#pragma once

#include "ge/asset.hpp"
#include "ge/material.hpp"
#include "ge/asset_manager.hpp"

#include "ge/json/json.h"

#include <memory>
#include <string>

/*
 * Asset Spec
 * 
 * {
 *   "asset_type": "material",
 *   "shader": "/asset/name/for/shader",
 *   "parameters": {
 *     "input_name": {uniform binding location (int)},
 *   }
 * } 
 * 
 */

namespace ge {

class material_asset : public asset 
{
public:
	std::shared_ptr<material> data;
	
	material_asset(asset_manager& manager, const std::string& name, const std::string& filepath, const Json::Value& json_data);
	
	static std::string asset_name(){ return "material"; }
};

}

