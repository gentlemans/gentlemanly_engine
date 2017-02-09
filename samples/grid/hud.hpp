#pragma once

#ifndef GRID_HUD_HPP
#define GRID_HUD_HPP

#include <ge/actor.hpp>

#include "grid.hpp"

#include <Rocket/Core.h>

class hud : public ge::actor
{
public:
	grid* g;
	Rocket::Core::ElementDocument* rdoc = nullptr;
	Rocket::Core::ElementText* text = nullptr;
	Rocket::Core::ElementText* resourceamount = nullptr;

	void initialize(grid* gr, Rocket::Core::ElementDocument* doc)
	{
		g = gr;
		rdoc = doc;
		add_interface<hud, gridtick_interface>();

		auto zcount = doc->GetElementById("zcount");
		if (!zcount) return;
		text = rdoc->CreateTextNode("0");
		zcount->AppendChild(text);

		auto resCount = doc->GetElementById("resamt");
		resourceamount = rdoc->CreateTextNode("0");
		resCount->AppendChild(resourceamount);
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
