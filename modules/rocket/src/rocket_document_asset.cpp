#include "ge/rocket_document_asset.hpp"
#include "ge/rocket_subsystem.hpp"

#include "ge/json_helper.hpp"
#include "ge/rocket_font_asset.hpp"

#include <boost/filesystem.hpp>

using namespace ge;

std::shared_ptr<Rocket::Core::ElementDocument> rocket_document_asset::load_asset(
	asset_manager& manager, const char* asset_name, const char* filepath,
	const nlohmann::json& json_data)
{
	using namespace std::string_literals;

	auto rml_file_iter = json_data.find("rml_file");
	if (rml_file_iter == json_data.end()) {
		logger->error("Rocket document asset "s + asset_name + " located at " + filepath +
					  " didn't specifiy a rml_file field. Document will not be loaded. See "
					  "https://gentlemans.github.io/gentlemanly_engine/"
					  "structge_1_1rocket__document__asset.html for more details.");

		return nullptr;
	}
	std::string doc = *rml_file_iter;

	std::string path = boost::filesystem::absolute(doc, filepath).string();

#ifndef _NDEBUG
	// make sure the path exists
	if (!boost::filesystem::is_regular_file(path)) {
		logger->error("The rml_file specified in the rocket document asset "s + asset_name +
					  " located at " + filepath +
					  " doesn't exist. The full path was evaluated to be " + path);
	}
#endif

	// load fonts
	auto fonts_iter = json_data.find("required_fonts");
	if (fonts_iter != json_data.end() && fonts_iter->is_array()) {
		for (const std::string& font_name : *fonts_iter) {
			manager.get_asset<rocket_font_asset>(font_name.c_str());
		}
	}

	// get rocket subsystem
	auto rocketsub = manager.m_runtime->get_subsystem<rocket_subsystem>();
	if (!rocketsub) {
		logger->error(
			"Cannot load a rocket document without a rocket_subsystem loaded. Failing to load "
			"asset...");
		return nullptr;
	}

	return std::shared_ptr<Rocket::Core::ElementDocument>(
		rocketsub->m_context->LoadDocument(path.c_str()), [](Rocket::Core::ElementDocument*) {});
}
