#pragma once

#ifndef GRID_HUD_HPP
#define GRID_HUD_HPP

#include <ge/actor.hpp>

#include "grid.hpp"

#include <Rocket/Core.h>

class open_piece_browser_eventlistener : public Rocket::Core::EventListener {
	void ProcessEvent(Rocket::Core::Event& event) override {
		
	}

};

class open_piece_browser_instancer : public Rocket::Core::EventListenerInstancer
{
	// Instance an event listener object.
	// @param value Value of the event.
	Rocket::Core::EventListener* InstanceEventListener(const Rocket::Core::String& value, Rocket::Core::Element* element) override {
		return nullptr;
	}

	// Releases this event listener instancer.Element* elementElElement* elementement* element
	void Release() override {
		
	}
};

class hud : public ge::actor
{
public:
	grid* g;
	Rocket::Core::ElementDocument* rdoc = nullptr;
	Rocket::Core::ElementText* text = nullptr;
	Rocket::Core::ElementText* resourceamount = nullptr;

	void initialize(grid* gr, ge::camera_actor* camera)
	{
		
		// load UI
		auto doc = m_runtime->m_asset_manager.get_asset<ge::rocket_document_asset>("gridui/doc.rocketdocument");
		doc->Show();


		auto pieceSelector =
			m_runtime->m_asset_manager.get_asset<ge::rocket_document_asset>("gridui/piecebrowser.rocketdocument");
		pieceSelector->Show();
		pieceSelector->PullToFront();

		
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

		auto& sdl = *m_runtime->get_subsystem<ge::sdl_subsystem>();
		auto& rocket = *m_runtime->get_subsystem<ge::rocket_subsystem>();
		
		Rocket::Core::Factory::RegisterEventListenerInstancer(new open_piece_browser_instancer);
		rocket.m_context->AddEventListener("showpiecemenu", new open_piece_browser_eventlistener);
		

		auto griddoc = rocket.m_context->CreateDocument("body");
		griddoc->Show();

		// create virtual rocket elements
		auto vp = camera->get_vp_matrix();
		auto tmpActor = actor::factory<piece>(g, glm::ivec3(0, 0, 0));
		for (int x = 0; x < 11; ++x) {
			for (int y = 0; y < 11; ++y) {
				auto start = vp * tmpActor->calculate_model_matrix() * glm::vec3(x - .5, y + .5, 1);
				auto end = vp * tmpActor->calculate_model_matrix() * glm::vec3(x + .5, y + 1.5, 1);

				start += 1;
				start.x *= (float)sdl.get_size().x / 2.f;
				start.y *= (float)sdl.get_size().y / 2.f;

				end += 1;
				end.x *= (float)sdl.get_size().x / 2.f;
				end.y *= (float)sdl.get_size().y / 2.f;

				auto xml = Rocket::Core::XMLAttributes();
				xml.Set("idx", x);
				xml.Set("idy", y);
				xml.Set("start", Rocket::Core::Vector2f{start.x, sdl.get_size().y - start.y});
				xml.Set("size", Rocket::Core::Vector2f{end.x - start.x, end.y - start.y});

				auto elem = Rocket::Core::Factory::InstanceElement(
					nullptr, "grid_rocket", "grid_rocket", xml);
				griddoc->AppendChild(elem);

				auto str = "grid_" + std::to_string(x) + "_" + std::to_string(y);
				elem->SetId(str.c_str());
			}
		}
	}

	void tick_grid()
	{
		int zcount = g->get_z_count();

		if (!text) return;
		text->SetText(std::to_string(zcount).c_str());
		resourceamount->SetText(std::to_string(g->get_resources()).c_str());
	}
};

#endif  // GRID_HUD_HPP
