#pragma once

#include "ge/json.hpp"

#include <boost/concept_check.hpp>

namespace ge
{
class asset_manager;

namespace concept
{
template <typename X>
struct Asset
{
	BOOST_CONCEPT_USAGE(Asset)
	{
		X i(*(asset_manager*)nullptr, "name", "filepath", nlohmann::json{});

		const char* type = X::asset_type();
	}
};
}
}
