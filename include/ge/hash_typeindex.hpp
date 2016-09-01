#ifndef GE_HASH_TYPEINDEX_HPP
#define GE_HASH_TYPEINDEX_HPP

#pragma once

#include <boost/functional/hash.hpp>
#include <boost/type_index.hpp>

namespace std
{
template <>
struct hash<boost::typeindex::type_index> {
	size_t operator()(const boost::typeindex::type_index& id) const { return id.hash_code(); }
};
}

#endif  // GE_HASH_TYPEINDEX_HPP
