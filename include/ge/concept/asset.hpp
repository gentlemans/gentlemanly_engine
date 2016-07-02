#ifndef GE_ASSET_HPP
#define GE_ASSET_HPP

#pragma once

#include "ge/json.hpp"

#include <boost/concept_check.hpp>

namespace ge
{
class asset_manager;

namespace concept
{
/// A concpet defining what an asset class looks like.
template <typename X>
struct Asset {
	using loaded_type = typename X::loaded_type;

	BOOST_CONCEPT_USAGE(Asset) { const char* type = X::asset_type(); }
};
}
}

#endif // GE_ASSET_HPP
