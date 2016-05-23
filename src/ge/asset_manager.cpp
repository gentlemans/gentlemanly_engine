#include "ge/asset_manager.hpp"

#include <boost/filesystem.hpp>

#include <algorithm>
#include <fstream>

namespace ge
{
void asset_manager::add_asset_path(std::string path, uint8_t priority)
{
	search_paths[priority].emplace_back(std::move(path));
}
}
