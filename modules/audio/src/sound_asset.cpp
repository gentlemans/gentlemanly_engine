#include "ge/sound_asset.hpp"

#include <boost/filesystem.hpp>

using namespace ge;

std::shared_ptr<sound> sound_asset::load_asset(
	asset_manager& manager, const char* name, const char* filepath, const nlohmann::json& json_data)
{
	namespace fs = boost::filesystem;
	// get absolute path

	std::string file = json_data["sound_file"];

	std::string abs_path = fs::absolute(file, filepath).string();

	return std::make_shared<sound>(abs_path.c_str());
}
