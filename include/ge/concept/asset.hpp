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
	using loaded_type = typename X::loaded_type;

	BOOST_CONCEPT_USAGE(Asset) { const char* type = X::asset_type(); }
};
}
}
