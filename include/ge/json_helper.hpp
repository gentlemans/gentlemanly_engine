#pragma once

#include "ge/json.hpp"

#include <string>

namespace ge
{
template <typename T>
inline T json_get_value_with_fallback(
	const nlohmann::json& obj, const std::string& value, const T& fallback)
{
	auto iter = obj.find(value);
	if (iter == obj.end())
	{
		return fallback;
	}

	return *iter;
}
}
