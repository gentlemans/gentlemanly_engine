#pragma once

#ifndef GRID_HUD_HPP
#define GRID_HUD_HPP

#include <ge/actor.hpp>
#include <ge/camera_actor.hpp>
#include <ge/sdl_subsystem.hpp>
#include <ge/rocket_subsystem.hpp>
#include <ge/rocket_document_asset.hpp>

#include "grid.hpp"
#include "event_manager.hpp"

#include <Rocket/Core.h>

class hud : public ge::actor
{
public:
	
	enum grid_mode {
		hitting,
		placing,
	};
	
	static hud* instance;
	
	void initialize(grid* gr, ge::camera_actor* camera);
	
	void grid_clicked(glm::ivec2 loc);
	
	bool pieceselector_visible();
	void show_pieceselector();
	void hide_pieceselector();
	
	void tick_grid();
private:
	
	grid* g;
	Rocket::Core::ElementDocument* rdoc = nullptr, *griddoc = nullptr, *pieceSelector;
	Rocket::Core::ElementText* text = nullptr;
	Rocket::Core::ElementText* resourceamount = nullptr;
	
	Rocket::Core::Element* clickedElement = nullptr;
	
	grid_mode m_mode = hitting;
	bool m_pieceselector_visible;

};

#endif  // GRID_HUD_HPP
