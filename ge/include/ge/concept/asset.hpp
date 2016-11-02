#ifndef GE_ASSET_HPP
#define GE_ASSET_HPP

#pragma once

#include <boost/concept_check.hpp>

#include "ge/json.hpp"

#include <type_traits>

namespace ge
{
class asset_manager;

namespace concept
{
/// A concpet defining what an asset class looks like.
template <typename X>
struct Asset {
	/// Make sure it defines a loaded type
	using loaded_type = typename X::loaded_type;

	/// Make sure it has a static asset_type function
	BOOST_CONCEPT_USAGE(Asset)
	{
		static_assert(std::is_convertible<decltype(X::asset_type()), const char*>::value,
			"Must have a asset_type function that returns char*");

		static_assert(std::is_same<decltype(X::load_asset(
									   *static_cast<asset_manager*>(0), "", "", nlohmann::json{})),
						  std::shared_ptr<loaded_type>>::value,
			"load asset returns the wrong type. see "
			"https://github.com/gentlemans/gentlemanly_engine/blob/master/doc/asset.md");
	}
};
}
}

#endif  // GE_ASSET_HPP
