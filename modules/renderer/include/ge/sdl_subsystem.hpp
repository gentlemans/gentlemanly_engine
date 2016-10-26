#ifndef GE_SDL_SUBSYSTEM_HPP
#define GE_SDL_SUBSYSTEM_HPP

#pragma once

#include "ge/camera_actor.hpp"
#include "ge/input_event.hpp"
#include "ge/subsystem.hpp"

#include <glm/glm.hpp>

#include <boost/optional.hpp>
#include <boost/signals2.hpp>

#include <memory>
#include <vector>

struct SDL_Window;

namespace ge
{
/// A subsystem that uses SDL to open a window and draw in it
struct sdl_subsystem : subsystem {
	/// The subsystem config
	struct config {
		/// Constructor
		config(const std::string& str, glm::uvec2 sz, boost::optional<glm::uvec2> loc = {},
			bool fullscr = false, bool decor = true)
			: title(str), size(sz), location(loc), fullscreen(fullscr), decorated(decor)
		{
		}

		/// The title of the window
		std::string title;

		///  The size of the window
		glm::uvec2 size;

		/// The location of the window on the screen, or {} to let the OS decide
		boost::optional<glm::uvec2> location;

		/// Should the window be fullscreen?
		bool fullscreen = false;

		/// Should it have decorations (minimize button, borders, etc)
		bool decorated = true;
	};

	/// The subsystem initialize function
	bool initialize(const config& conf);

	/// The update function from `subsystem`
	virtual bool update(std::chrono::duration<float> delta) override;

	/// The shutdown function from `subsystem`
	virtual bool shutdown() override;

	/// Gets the size of the window
	/// \return The size of the window
	glm::uvec2 get_size() const;

	/// Set the size of the window
	/// \param new_size Set the size of the window
	void set_size(glm::uvec2 new_size);

	/// Gets the title of the window
	/// \return The title
	std::string get_title() const;

	/// Sets the title of the window
	/// \param newTitle The new title
	void set_title(const std::string& newTitle);

	/// Sets the background color of the viewport where there are no polygons
	/// \param newColor The new color
	void set_background_color(const glm::vec3& newColor) noexcept { m_background_color = newColor; }
	/// Gets the background color of the viewport
	/// \return The background color
	glm::vec3 get_background_color() const noexcept { return m_background_color; }
	/// Get the camera actor to view from
	/// \return The camera
	camera_actor* get_camera() const noexcept { return m_camera.get(); }
	/// Set the camera actor
	/// \param cam The new camera to view from
	void set_camera(camera_actor* cam) noexcept { m_camera = actor::shared(cam); }
	/// Gets the root actor to draw all subactors from
	/// \return The root actor

	/// Signal to connect to if you want a render callback
	boost::signals2::signal<void()> m_render_signal;

private:
	void* m_context = nullptr;  // turns out SDL_GLContext is literally just void*
	SDL_Window* m_window = nullptr;
	glm::vec3 m_background_color;
	std::shared_ptr<camera_actor> m_camera;
};

}  // namespace ge

#endif  // GE_SDL_SUBSYSTEM_HPP
