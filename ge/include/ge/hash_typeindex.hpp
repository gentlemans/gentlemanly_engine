#ifndef GE_HASH_TYPEINDEX_HPP
#define GE_HASH_TYPEINDEX_HPP

#pragma once

#include <boost/type_index.hpp>

namespace std
{
/// Hasher for `boost::typeinfo::type_index` so it can be used as the key in an `unordered_map` or
/// `unordered_set`
template <>
struct hash<boost::typeindex::type_index> {
	/// The hash function
	size_t operator()(const boost::typeindex::type_index& id) const { return id.hash_code(); }
};
}

#endif  // GE_HASH_TYPEINDEX_HPP
