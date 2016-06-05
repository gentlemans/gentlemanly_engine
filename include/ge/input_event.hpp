#pragma once

#include <glm/glm.hpp>

#include <boost/variant.hpp>

namespace ge
{
enum class key
{
	// modifiers
	e_left_shift,
	e_right_shift,
	e_left_meta,
	e_right_meta,
	e_left_alt,
	e_right_alt,
	e_left_ctrl,
	e_right_ctrl,

	e_0 = '0',
	e_1 = '1',
	e_2 = '2',
	e_3 = '3',
	e_4 = '4',
	e_5 = '5',
	e_6 = '6',
	e_7 = '7',
	e_8 = '8',
	e_9 = '9',
	e_minus = '-',
	e_equals = '=',

	e_a = 'a',
	e_b = 'b',
	e_c = 'c',
	e_d = 'd',
	e_e = 'e',
	e_f = 'f',
	e_g = 'g',
	e_h = 'h',
	e_i = 'i',
	e_j = 'j',
	e_k = 'k',
	e_l = 'l',
	e_m = 'm',
	e_n = 'n',
	e_o = 'o',
	e_p = 'p',
	e_q = 'q',
	e_r = 'r',
	e_s = 's',
	e_t = 't',
	e_u = 'u',
	e_v = 'v',
	e_w = 'w',
	e_x = 'x',
	e_y = 'y',
	e_z = 'z',

	e_comma = ',',
	e_period = '.',
	e_forward_slash = '/',
	e_backward_slash = '\\',
	e_backspace = '\b',
	e_return = '\r',
	e_semicolon = ';',
	e_apostrophe = '\'',
	e_back_tick = '`',
	e_space = ' ',

	e_escape = '\033',

	e_insert,
	e_delete = '\177',
	e_home,
	e_end,
	e_page_up,
	e_page_down,
	e_print_screen,
	e_scroll_lock,
	e_pause,

	e_left_bracket = '[',
	e_right_bracket = ']',

	e_tab = '\t',
	e_caps_lock,

	e_F0,
	e_F1,
	e_F2,
	e_F3,
	e_F4,
	e_F5,
	e_F6,
	e_F7,
	e_F8,
	e_F9,
	e_F10,
	e_F11,
	e_F12,

	// numpad
	e_numpad_0,
	e_numpad_1,
	e_numpad_2,
	e_numpad_3,
	e_numpad_4,
	e_numpad_5,
	e_numpad_6,
	e_numpad_7,
	e_numpad_8,
	e_numpad_9,

	e_num_lock,
	e_numpad_divide,
	e_numpad_times,
	e_numpad_minus,
	e_numpad_plus,
	e_numpad_enter,
	e_numpad_period,

	e_left,
	e_up,
	e_down,
	e_right,

};

struct input_keyboard
{
	key input_key;

	// false for released
	bool pressed;
	
	bool operator==(const input_keyboard& other) const {
		return this->input_key == other.input_key &&
			this->pressed == other.pressed;
	}
	
	bool operator!=(const input_keyboard& other) const {
		return !(*this == other);
	}
};

enum class mouse_button
{
	e_left_button,
	e_right_button,
	e_middle_button,
	e_button_1,
	e_button_2,
};

struct input_mouse_move
{
	glm::vec2 new_location;
	
	bool operator==(const input_mouse_move& other) const {
		return new_location == other.new_location;
	}
	bool operator!=(const input_mouse_move& other) const {
		return !(*this == other);
	}
};

struct input_mouse_button
{
	mouse_button m_button;
	bool pressed;  // false for released
	
		bool operator==(const input_mouse_button& other) const {
		return m_button == other.m_button &&
			pressed == other.pressed;
	}
	bool operator!=(const input_mouse_button& other) const {
		return !(*this == other);
	}
};

struct input_none
{
	bool operator==(input_none) const { return true; }
	bool operator!=(input_none) const { return false; }
};

using input_event =
	boost::variant<input_keyboard, input_mouse_move, input_mouse_button, input_none>;
}
