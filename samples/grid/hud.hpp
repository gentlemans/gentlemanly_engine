#pragma once

#ifndef GRID_HUD_HPP
#define GRID_HUD_HPP

#include <ge/actor.hpp>
#include <ge/camera_actor.hpp>
#include <ge/sdl_subsystem.hpp>
#include <ge/rocket_subsystem.hpp>
#include <ge/rocket_document_asset.hpp>

#include "grid.hpp"
#include "grid_rocket_element.hpp"
#include "event_manager.hpp"

#include <Rocket/Core.h>

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
	Rocket::Core::ElementDocument* rdoc = nullptr, *griddoc = nullptr, *pieceSelector;;
	Rocket::Core::ElementText* text = nullptr;
	Rocket::Core::ElementText* resourceamount = nullptr;

	void initialize(grid* gr, ge::camera_actor* camera);
	
	void tick_grid();
};

#endif  // GRID_HUD_HPP
