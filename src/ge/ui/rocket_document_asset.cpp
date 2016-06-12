#include "ge/ui/rocket_document_asset.hpp"

#include "ge/json_helper.hpp"
#include "ge/ui/rocket_font_asset.hpp"

#include <boost/filesystem.hpp>

namespace ge
{
namespace ui
{
std::shared_ptr<Rocket::Core::ElementDocument> rocket_document_asset::load_asset(asset_manager& manager,
	const char* asset_name, const char* filepath, const nlohmann::json& json_data,
	Rocket::Core::Context* ctx)
{
	using namespace std::string_literals;

	std::string path = boost::filesystem::absolute(json_get_value_with_fallback(json_data, "rml_file"s, "doc.rml"s), filepath).string();
	
	// load fonts
	auto fonts_iter = json_data.find("required_fonts");
	if(fonts_iter != json_data.end() && fonts_iter->is_array()) {
		for(const std::string& font_name : *fonts_iter) {
			manager.get_asset<rocket_font_asset>(font_name.c_str());
		}
	}
	
	return std::shared_ptr<Rocket::Core::ElementDocument>(ctx->LoadDocument(path.c_str()), [](Rocket::Core::ElementDocument* doc){  });
}
}
}
