#pragma once

#include <string>
#include <ctime>

namespace ge
{
class asset
{
protected:
	std::string type;
	std::string name;
	std::string absolute_path;

public:
	asset(std::string arg_type, std::string arg_name, std::string arg_absolute_path)
		: type{std::move(arg_type)},
		  name{std::move(arg_name)},
		  absolute_path{std::move(arg_absolute_path)}
	{
	}

	virtual ~asset() = default;

	const std::string& get_type() const { return type; }
	const std::string& get_name() const { return name; }
	const std::string& get_absolute_path() const { return absolute_path; }
};
}
