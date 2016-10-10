#include "ge/sdl_subsystem.hpp"
#include "ge/gl.hpp"

#include "SDL.h"

#include "ge/input_subsystem.hpp"

#include <chrono>

using namespace ge;

key sdl_to_ge_key(SDL_Keycode code)
{
	switch (code) {
	case SDLK_EXCLAIM: return key::e_1;
	case SDLK_QUOTEDBL: return key::e_apostrophe;
	case SDLK_HASH: return key::e_3;
	case SDLK_PERCENT: return key::e_5;
	case SDLK_DOLLAR: return key::e_4;
	case SDLK_AMPERSAND: return key::e_7;
	case SDLK_LEFTPAREN: return key::e_9;
	case SDLK_RIGHTPAREN: return key::e_0;
	case SDLK_ASTERISK: return key::e_8;
	case SDLK_PLUS: return key::e_equals;
	case SDLK_LESS: return key::e_comma;
	case SDLK_GREATER: return key::e_period;
	case SDLK_QUESTION: return key::e_forward_slash;
	case SDLK_AT: return key::e_2;
	case SDLK_CARET: return key::e_6;
	case SDLK_UNDERSCORE: return key::e_minus;
	case SDLK_CAPSLOCK: return key::e_caps_lock;
	case SDLK_F1: return key::e_F1;
	case SDLK_F2: return key::e_F2;
	case SDLK_F3: return key::e_F3;
	case SDLK_F4: return key::e_F4;
	case SDLK_F5: return key::e_F5;
	case SDLK_F6: return key::e_F6;
	case SDLK_F7: return key::e_F7;
	case SDLK_F8: return key::e_F8;
	case SDLK_F9: return key::e_F9;
	case SDLK_F10: return key::e_F10;
	case SDLK_F11: return key::e_F11;
	case SDLK_F12: return key::e_F12;
	case SDLK_PRINTSCREEN: return key::e_print_screen;
	case SDLK_SCROLLLOCK: return key::e_scroll_lock;
	case SDLK_PAUSE: return key::e_pause;
	case SDLK_INSERT: return key::e_insert;
	case SDLK_HOME: return key::e_home;
	case SDLK_PAGEUP: return key::e_page_up;
	case SDLK_PAGEDOWN: return key::e_page_down;
	case SDLK_END: return key::e_end;
	case SDLK_RIGHT: return key::e_right;
	case SDLK_LEFT: return key::e_left;
	case SDLK_UP: return key::e_up;
	case SDLK_DOWN: return key::e_down;
	case SDLK_NUMLOCKCLEAR: return key::e_num_lock;
	case SDLK_KP_DIVIDE: return key::e_numpad_divide;
	case SDLK_KP_PLUS: return key::e_numpad_plus;
	case SDLK_KP_MULTIPLY: return key::e_numpad_times;
	case SDLK_KP_MINUS: return key::e_numpad_minus;
	case SDLK_KP_ENTER: return key::e_numpad_enter;
	case SDLK_KP_0: return key::e_numpad_0;
	case SDLK_KP_1: return key::e_numpad_1;
	case SDLK_KP_2: return key::e_numpad_2;
	case SDLK_KP_3: return key::e_numpad_3;
	case SDLK_KP_4: return key::e_numpad_4;
	case SDLK_KP_5: return key::e_numpad_5;
	case SDLK_KP_6: return key::e_numpad_6;
	case SDLK_KP_7: return key::e_numpad_7;
	case SDLK_KP_8: return key::e_numpad_8;
	case SDLK_KP_9: return key::e_numpad_9;
	case SDLK_LCTRL: return key::e_left_ctrl;
	case SDLK_RCTRL: return key::e_right_ctrl;
	case SDLK_LALT: return key::e_left_alt;
	case SDLK_RALT: return key::e_right_alt;
	case SDLK_LSHIFT: return key::e_left_shift;
	case SDLK_RSHIFT: return key::e_right_shift;
	case SDLK_LGUI: return key::e_left_meta;
	case SDLK_RGUI: return key::e_right_meta;
	}

	// if we are still here, it is convertable
	return static_cast<key>(code);
}

mouse_button sdl_mb_to_ge(Uint8 button)
{
	switch (button) {
	case SDL_BUTTON_LEFT: return mouse_button::e_left_button;
	case SDL_BUTTON_MIDDLE: return mouse_button::e_middle_button;
	case SDL_BUTTON_RIGHT: return mouse_button::e_right_button;
	case SDL_BUTTON_X1: return mouse_button::e_button_1;
	case SDL_BUTTON_X2: return mouse_button::e_button_2;
	}
	return static_cast<mouse_button>(0);
}

int sdl_mods_to_ge(int mod)
{
	int ret = 0x0;

	if (mod & KMOD_LSHIFT) ret |= key_modifier::e_left_shift;
	if (mod & KMOD_RSHIFT) ret |= key_modifier::e_right_shift;
	if (mod & KMOD_LCTRL) ret |= key_modifier::e_left_ctrl;
	if (mod & KMOD_RCTRL) ret |= key_modifier::e_right_ctrl;
	if (mod & KMOD_LALT) ret |= key_modifier::e_left_alt;
	if (mod & KMOD_RALT) ret |= key_modifier::e_right_alt;
	if (mod & KMOD_LGUI) ret |= key_modifier::e_left_gui;
	if (mod & KMOD_RGUI) ret |= key_modifier::e_right_gui;
	if (mod & KMOD_NUM) ret |= key_modifier::e_num_lock;
	if (mod & KMOD_CAPS) ret |= key_modifier::e_caps_lock;

	return ret;
}

bool sdl_subsystem::initialize(const sdl_subsystem::config& config)
{
	SDL_Init(SDL_INIT_VIDEO);

	// create the window
	int flags = SDL_WINDOW_OPENGL | (config.fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0) |
				(config.decorated ? 0 : SDL_WINDOW_BORDERLESS);
#ifndef EMSCRIPTEN
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
#endif

	glm::uvec2 loc = config.location ? config.location.get()
									 : glm::uvec2{SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED};

	// initalize the window
	m_window =
		SDL_CreateWindow(config.title.c_str(), loc.x, loc.y, config.size.x, config.size.y, flags);

	using namespace std::string_literals;
	if (!m_window) {
		log->error("Error initalizing SDL window"s + SDL_GetError());
		return false;
	}
	// create the context
	m_context = SDL_GL_CreateContext(m_window);
	SDL_GL_MakeCurrent(m_window, m_context);

#ifdef WIN32
	if (!gladLoadGL()) {
		log->error("Failed to load OpenGL functions from glad");
		return false;
	}
#endif

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return true;
}

bool sdl_subsystem::update(std::chrono::duration<float> delta)
{
	SDL_GL_SwapWindow(m_window);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(m_background_color.r, m_background_color.g, m_background_color.b, 1.f);

	static auto last_tick = std::chrono::system_clock::now();
	auto now = std::chrono::system_clock::now();

	std::chrono::duration<float> diff = now - last_tick;

	// app->signal_update(diff.count());
	// app->elapsed_time += diff.count();

	last_tick = now;

	SDL_Event event;

	auto input_sub = m_runtime->get_subsystem<input_subsystem>();

	// run until there is an event that we recognize
	while (SDL_PollEvent(&event)) {
		input_event ev;
		switch (event.type) {
		case SDL_QUIT: return false;
		case SDL_KEYDOWN:
			if (!event.key.repeat)
				ev = input_keyboard{sdl_to_ge_key(event.key.keysym.sym), true,
					sdl_mods_to_ge(event.key.keysym.mod)};
			break;
		case SDL_KEYUP:
			if (!event.key.repeat)
				ev = input_keyboard{sdl_to_ge_key(event.key.keysym.sym), false,
					sdl_mods_to_ge(event.key.keysym.mod)};
			break;
		case SDL_MOUSEMOTION:
			ev = input_mouse_move{
				{event.motion.x, event.motion.y}, sdl_mods_to_ge(SDL_GetModState())};
			break;
		case SDL_MOUSEBUTTONDOWN:
			ev = input_mouse_button{sdl_mb_to_ge(event.button.button), true,
				sdl_mods_to_ge(SDL_GetModState()), {event.button.x, event.button.x}};
			break;
		case SDL_MOUSEBUTTONUP:
			ev = input_mouse_button{sdl_mb_to_ge(event.button.button), false,
				sdl_mods_to_ge(SDL_GetModState()), {event.button.x, event.button.x}};
			break;
		case SDL_MOUSEWHEEL:
			if (event.wheel.direction == SDL_MOUSEWHEEL_NORMAL) {
				ev = input_scroll_wheel{
					{event.wheel.x, event.wheel.y}, sdl_mods_to_ge(SDL_GetModState())};
			} else {
				ev = input_scroll_wheel{
					{-event.wheel.x, -event.wheel.y}, sdl_mods_to_ge(SDL_GetModState())};
			}
			break;
		}
		if (input_sub) {
			input_sub->add_event(ev);
		}
	}

	// render!
	if (m_camera) {
		m_camera->render_actors(
			*m_runtime->get_root_actor(), float(get_size().x) / float(get_size().y));
	}

	return true;
}

bool sdl_subsystem::shutdown()
{
	SDL_GL_DeleteContext(m_context);
	SDL_DestroyWindow(m_window);
	SDL_Quit();

	return true;
}

glm::uvec2 sdl_subsystem::get_size() const
{
	glm::ivec2 ret;
	SDL_GetWindowSize(m_window, &ret.x, &ret.y);

	return ret;
}
void sdl_subsystem::set_size(glm::uvec2 new_size)
{
	SDL_SetWindowSize(m_window, new_size.x, new_size.y);
}

std::string sdl_subsystem::get_title() const { return SDL_GetWindowTitle(m_window); }
void sdl_subsystem::set_title(const std::string& newTitle)
{
	SDL_SetWindowTitle(m_window, newTitle.c_str());
}
