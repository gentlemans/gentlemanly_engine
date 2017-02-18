#pragma once

#ifndef GRID_GRID_CAMERA_HPP
#define GRID_GRID_CAMERA_HPP

#include <ge/camera_actor.hpp>
#include <ge/tickable.hpp>

class grid_camera : public ge::camera_actor {
public:

	void initialize(int grid_size, float aspect_ratio) {
		m_grid_size = grid_size;
		m_aspect_ratio = aspect_ratio;

		set_relative_location(reset_location());
		reset_zoom();
		
		starting = dest = get_relative_location();
		add_interface<grid_camera, ge::tickable>();
	}

	glm::mat3 dest_vp_mat() {
		glm::vec2 oldloc = get_relative_location();
		
		set_relative_location(dest);
		
		glm::mat3 ret = get_vp_matrix();
		
		set_relative_location(oldloc);
		
		return ret;
	}
	
	glm::vec2 reset_location() const {


		// move the camera to the default location

		if (m_aspect_ratio < 1) {
			auto m_flipped_ratio = 1 / m_aspect_ratio;

			auto ratio_on_top = (m_flipped_ratio - 1) / 2;

			auto amount_to_move = ratio_on_top * m_grid_size * m_aspect_ratio + 1;

			return {0, amount_to_move};
		} else {
			return {0, 0};
		}
		
	}
	
	void reset_zoom() {
		if (m_aspect_ratio > 1) {
			// this means that it's widescreen

			m_vertical_units = float(m_grid_size);
		}
		else {
			// this means it's portrait

			m_vertical_units = m_grid_size * (1 / m_aspect_ratio);
		}

	}
	
	void tick(std::chrono::duration<float> delta) {
		set_relative_location(ge::interpolate_to(starting, dest, get_relative_location(), .2, delta.count()));
	}


	glm::vec2 center_piece_loc(glm::ivec2 id) {

		return reset_location() + glm::vec2((m_grid_size / 2) - id.x, (m_grid_size - id.y - 1));
	}
	
	void smooth_move(glm::vec2 moveTo) {
		starting = get_relative_location();
		dest = moveTo;
	}
	
	glm::vec2 starting, dest;
	int m_grid_size;

};

#endif // GRID_GRID_CAMERA_HPP
