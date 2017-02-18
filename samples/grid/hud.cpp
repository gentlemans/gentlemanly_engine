#include "grid_rocket_element.hpp"
#include "hud.hpp"
#include "wall.hpp"
#include "zombie.hpp"

hud* hud::instance = nullptr;

void hud::initialize(grid* gr, grid_camera* camera)
{
	m_camera = camera;
	instance = this;
	
	// fill with zeros
	m_grid_elements.fill({{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}});

	initialze_event_manager();
	register_event("showpiecemenu", [this](Rocket::Core::Event& ev, const std::string& args) {

		if (pieceselector_visible()) {
			hide_pieceselector();
			m_mode = hitting;
		} else {
			show_pieceselector();
			m_mode = placing;
		}

	});
	register_event("clickpiece", [this](Rocket::Core::Event& ev, const std::string& args) {
		if (clickedElement != nullptr) {
			// if we clicked on the same one again
			if (clickedElement->GetId().CString() == args) {
				clickedElement->SetPseudoClass("clicked", false);
				clickedElement = nullptr;

				return;
			}
			clickedElement->SetPseudoClass("clicked", false);
		}
		clickedElement = ev.GetTargetElement()->GetOwnerDocument()->GetElementById(args.c_str());
		clickedElement->SetPseudoClass("clicked", true);
		hide_pieceselector(); 
		clickedElement->SetPseudoClass("clicked", false);
		pieceSelector->Hide();
		
		griddoc->PullToFront();
	});
	
	register_event("rotate", [this](Rocket::Core::Event&, const std::string& direction) {
		if (detailing == nullptr) {
			return;
		}
		
		if (direction == "north") {
			detailing->rotate(piece::NORTH);
		} else if (direction == "south") {
			detailing->rotate(piece::SOUTH);
		} else if (direction == "west") {
			detailing->rotate(piece::WEST);
		} else if (direction == "east") {
			detailing->rotate(piece::EAST);
		}
	});
	

	register_event("goback", [this](Rocket::Core::Event&, const std::string& ) {
		back_action();
	});
	
	register_event("delete", [this](Rocket::Core::Event&, const std::string&) {
		if (detailing != nullptr) {
			detailing->set_parent(nullptr);
			back_action();
		}
	});

	// load UI
	auto doc = m_runtime->m_asset_manager.get_asset<ge::rocket_document_asset>(
		"gridui/doc.rocketdocument");
	doc->Show();

	pieceSelector = m_runtime->m_asset_manager
						.get_asset<ge::rocket_document_asset>("gridui/piecebrowser.rocketdocument")
						.get();

	details = m_runtime->m_asset_manager.get_asset<ge::rocket_document_asset>("gridui/details.rocketdocument").get();
						
	g = gr;
	rdoc = doc.get();
	add_interface<hud, gridtick_interface>();

	auto zcount = doc->GetElementById("zcount");
	if (!zcount) return;
	text = rdoc->CreateTextNode("0");
	zcount->AppendChild(text);

	auto resCount = doc->GetElementById("resamt");
	resourceamount = rdoc->CreateTextNode("0");
	resCount->AppendChild(resourceamount);

	grid_rocket_instancer::registerInstancer();

	auto& rocket = *m_runtime->get_subsystem<ge::rocket_subsystem>();

	griddoc = rocket.m_context->CreateDocument("body");
	griddoc->Show();

	generate_grid();
}

void hud::generate_grid() {
	
	auto& sdl = *m_runtime->get_subsystem<ge::sdl_subsystem>();
	
	// create virtual rocket elements
	auto vp = m_camera->dest_vp_mat();
	auto tmpActor = actor::factory<piece>(g, glm::ivec3(0, 0, 0));
	for (int x = 0; x < 11; ++x) {
		for (int y = 0; y < 11; ++y) {
			// if there's an existing element, delete it
			if (m_grid_elements[x][y] != nullptr) {
				griddoc->RemoveChild(m_grid_elements[x][y]);
				m_grid_elements[x][y] = nullptr;
			}
			
			auto mm = tmpActor->calculate_model_matrix();
			auto start = vp * mm * glm::vec3(x - .5, y + .5, 1);
			auto end = vp * mm * glm::vec3(x + .5, y + 1.5, 1);

			start += 1;
			start.x *= sdl.get_size().x / 2.f;
			start.y *= sdl.get_size().y / 2.f;

			end += 1;
			end.x *= sdl.get_size().x / 2.f;
			end.y *= sdl.get_size().y / 2.f;

			auto xml = Rocket::Core::XMLAttributes();
			xml.Set("idx", x);
			xml.Set("idy", y);
			xml.Set("start", Rocket::Core::Vector2f{start.x, sdl.get_size().y - start.y});
			xml.Set("size", Rocket::Core::Vector2f{end.x - start.x, end.y - start.y});

			auto elem =
				Rocket::Core::Factory::InstanceElement(nullptr, "grid_rocket", "grid_rocket", xml);
			griddoc->AppendChild(elem);
			elem->RemoveReference();
			m_grid_elements[x][y] = elem;

			auto str = "grid_" + std::to_string(x) + "_" + std::to_string(y);
			elem->SetId(str.c_str());
		}
	}
}

void hud::back_action() {
	details->Hide();
	
	m_camera->smooth_move(m_camera->reset_location());
	
	generate_grid();
	griddoc->PullToFront();
}

void hud::grid_clicked(glm::ivec2 loc)
{
	switch (m_mode) {
	case hitting: {
		// get the pieces here
		auto pieces = g->get_actors_at_coord({loc.x, loc.y});

		if (pieces.empty()) {
			return;
		}
		// see if there's a tower there

		piece* tower = nullptr;
		for (auto p : pieces) {
			if (typeid(*p) != typeid(zombie)) {
				tower = p;

				break;
			}
		}

		if (tower) {
			// zoom it on it
			m_camera->smooth_move(m_camera->center_piece_loc(loc));
//			m_camera->m_vertical_units = 6;
			generate_grid();
			m_grid_elements[loc.x][loc.y]->SetProperty("background-color", "rgba(0%, 100%, 0%, 20%)");
			
			detailing = tower;
			
			details->Show();
			details->PullToFront();
		}

		break;
	}
	case placing:
		if (clickedElement != nullptr) {
			auto id = clickedElement->GetId();
			if (id == "turret") {
				actor::factory<turret>(grid::instance, loc, piece::NORTH);
			} else if (id == "wall") {
				actor::factory<wall>(grid::instance, loc);
			}
		}
		break;
	}
}
bool hud::pieceselector_visible() { return m_pieceselector_visible; }
void hud::show_pieceselector()
{
	pieceSelector->Show();
	pieceSelector->PullToFront();
	m_pieceselector_visible = true;
}
void hud::hide_pieceselector()
{
	if (clickedElement != nullptr) {
		clickedElement->SetPseudoClass("clicked", false);
	}
	pieceSelector->Hide();
	m_pieceselector_visible = false;
}

void hud::tick_grid()
{
	int zcount = g->get_z_count();

	if (!text) return;
	text->SetText(std::to_string(zcount).c_str());
	resourceamount->SetText(std::to_string(g->get_resources()).c_str());
}
