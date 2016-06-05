#include "ge/sdl_viewport.hpp"
#include "ge/camera_component.hpp"
#include "ge/ortho2d.hpp"
#include "ge/sdl_window.hpp"

#include "SDL.h"

#include <GL/gl.h>

#include <stdexcept>

#include <glm/glm.hpp>


namespace ge
{


key sdl_to_ge_key(SDL_Keycode code) 
{
	switch(code){
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

mouse_button sdl_mb_to_ge(Uint8 button) {
	
	switch(button) {
		case SDL_BUTTON_LEFT: return mouse_button::e_left_button;
		case SDL_BUTTON_MIDDLE: return mouse_button::e_middle_button;
		case SDL_BUTTON_RIGHT: return mouse_button::e_right_button;
		case SDL_BUTTON_X1: return mouse_button::e_button_1;
		case SDL_BUTTON_X2: return mouse_button::e_button_2;

	}
	
}

sdl_viewport::sdl_viewport(ge::sdl_window& window_arg) : m_window{&window_arg} {}
void sdl_viewport::set_background_color(const glm::vec4& newColor)
{
	glClearColor(newColor.r, newColor.g, newColor.b, newColor.a);
}

input_event sdl_viewport::get_next_input_event() {
	
	SDL_Event event;
	
	SDL_PollEvent(&event);
	
	switch (event.type) {
		case SDL_KEYDOWN:
			return input_keyboard{sdl_to_ge_key(event.key.keysym.sym), true};
		case SDL_KEYUP:
			return input_keyboard{sdl_to_ge_key(event.key.keysym.sym), false};
		case SDL_MOUSEMOTION:
			return input_mouse_move{{event.motion.x, event.motion.y}};
		case SDL_MOUSEBUTTONDOWN:
			return input_mouse_button{sdl_mb_to_ge(event.button.button), true};
	}
	
}

}
