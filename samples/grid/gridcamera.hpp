#pragma once

#ifndef GRID_GRID_CAMERA_HPP
#define GRID_GRID_CAMERA_HPP

#include <ge/camera_actor.hpp>

class grid_camera : public ge::camera_actor {
public:

	void initialize(int grid_size, float aspect_ratio) {
		m_grid_size = grid_size;
		m_aspect_ratio = aspect_ratio;

		reset();
	}

	void reset() {

		if (m_aspect_ratio > 1) {
			// this means that it's widescreen

			m_vertical_units = float(m_grid_size);
		}
		else {
			// this means it's portrait

			m_vertical_units = m_grid_size * (1 / m_aspect_ratio);
		}

		// move the camera to the default location

		if (m_aspect_ratio < 1) {
			auto m_flipped_ratio = 1 / m_aspect_ratio;

			auto ratio_on_top = (m_flipped_ratio - 1) / 2;

			auto amount_to_move = ratio_on_top * m_grid_size + .5;

			set_relative_location(get_relative_location() + glm::vec2(0, amount_to_move));
		}
	}

	int m_grid_size;

	void center_piece(glm::ivec2 id) {
		reset();

		set_relative_location(get_relative_location() + glm::vec2((m_grid_size - id.x) / 2.f, (m_grid_size - id.y - 1)));
	}

};

#endif // GRID_GRID_CAMERA_HPP