#include "ge/ui/rocket_document_asset.hpp"

#include "ge/json_helper.hpp"

namespace ge
{
namespace ui
{
std::shared_ptr<Rocket::Core::ElementDocument> rocket_document_asset::load_asset(asset_manager& manager,
	const char* asset_name, const char* filepath, const nlohmann::json& json_data,
	Rocket::Core::Context* ctx)
{
	using namespace std::string_literals;

	return std::shared_ptr<Rocket::Core::ElementDocument>(ctx->LoadDocument(
		json_get_value_with_fallback(json_data, "rml_file"s, "doc.rml"s).c_str()));
}
}
}
