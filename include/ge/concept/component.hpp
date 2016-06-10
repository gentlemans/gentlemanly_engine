#pragma once

#include <boost/concept_check.hpp>

#include <boost/mpl/is_sequence.hpp>

namespace ge
{
namespace concept
{
template <typename X>
struct Component {
	using depends = typename X::depends;
	using implements = typename X::implements;

	static_assert(boost::mpl::is_sequence<depends>::value,
		"The depends type in a Component must be a boost::mpl::sequence (list or vector)");

private:
	X i;
};

}  // namespace concept
}  // namespace ge
