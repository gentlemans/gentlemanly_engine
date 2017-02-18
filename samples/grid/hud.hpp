#pragma once

#ifndef GRID_HUD_HPP
#define GRID_HUD_HPP

#include <vector>

#include <ge/actor.hpp>
#include <ge/camera_actor.hpp>
#include <ge/sdl_subsystem.hpp>
#include <ge/rocket_subsystem.hpp>
#include <ge/rocket_document_asset.hpp>

#include "grid.hpp"
#include "event_manager.hpp"
#include "gridcamera.hpp"

#include <Rocket/Core.h>

class hud : public ge::actor
{
public:
	
	enum grid_mode {
		hitting,
		placing,
	};
	
	static hud* instance;
	
	void initialize(grid* gr, grid_camera* camera);
	
	void grid_clicked(glm::ivec2 loc);
	
	bool pieceselector_visible();
	void show_pieceselector();
	void hide_pieceselector();
	
	void tick_grid();
	
	void back_action();
private:
	
	grid* g;
	grid_camera* m_camera;
	piece* detailing = nullptr;
	Rocket::Core::ElementDocument* rdoc = nullptr, *griddoc = nullptr, *pieceSelector, *details;
	Rocket::Core::ElementText* text = nullptr;
	Rocket::Core::ElementText* resourceamount = nullptr;
	
	Rocket::Core::Element* clickedElement = nullptr;
	
	grid_mode m_mode = hitting;
	bool m_pieceselector_visible;
	
	std::array<std::array<Rocket::Core::Element*, 11>, 11> m_grid_elements;

};

#endif  // GRID_HUD_HPP
