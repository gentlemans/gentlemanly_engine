#ifndef GE_INPUT_EVENT_HPP
#define GE_INPUT_EVENT_HPP

#pragma once

#include <glm/glm.hpp>

#include <boost/variant.hpp>

namespace ge
{
/// A key on a standard keyboard
enum class key {

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
	e_delete = '\177',

	e_left_bracket = '[',
	e_right_bracket = ']',

	e_tab = '\t',

	e_F1 = 999,
	e_F2 = 1000,
	e_F3 = 1001,
	e_F4 = 1002,
	e_F5 = 1003,
	e_F6 = 1004,
	e_F7 = 1005,
	e_F8 = 1006,
	e_F9 = 1007,
	e_F10 = 1008,
	e_F11 = 1009,
	e_F12 = 1010,

	// numpad
	e_numpad_0 = 1011,
	e_numpad_1 = 1012,
	e_numpad_2 = 1013,
	e_numpad_3 = 1014,
	e_numpad_4 = 1015,
	e_numpad_5 = 1016,
	e_numpad_6 = 1017,
	e_numpad_7 = 1018,
	e_numpad_8 = 1019,
	e_numpad_9 = 1020,

	e_num_lock = 1020,
	e_numpad_divide = 1021,
	e_numpad_times = 1022,
	e_numpad_minus = 1023,
	e_numpad_plus = 1024,
	e_numpad_enter = 1025,
	e_numpad_period = 1026,

	e_left = 1027,
	e_up = 1028,
	e_down = 1029,
	e_right = 1030,

	e_insert = 1031,
	e_home = 1032,
	e_end = 1033,
	e_page_up = 1034,
	e_page_down = 1035,
	e_print_screen = 1036,
	e_scroll_lock = 1037,
	e_pause = 1038,

	e_caps_lock = 1039,

	// modifiers
	e_left_shift = 1040,
	e_right_shift = 1041,
	e_left_meta = 1042,
	e_right_meta = 1043,
	e_left_alt = 1044,
	e_right_alt = 1045,
	e_left_ctrl = 1046,
	e_right_ctrl = 1047,
};

/// The standard modifiers
namespace key_modifier
{
enum {
	e_left_shift = 0b1,
	e_right_shift = 0b10,
	e_right_ctrl = 0b100,
	e_left_ctrl = 0b1000,
	e_caps_lock = 0b10000,
	e_num_lock = 0b100000,
	e_scroll_lock = 0b1000000,
	e_left_gui = 0b10000000,
	e_right_gui = 0b100000000,
	e_left_alt = 0b1000000000,
	e_right_alt = 0b10000000000
};
}

/// A input event from the keyboard
struct input_keyboard {
	/// Default constructor
	input_keyboard() = default;

	/// Copy constructor
	/// \param event Event to copy from
	input_keyboard(const input_keyboard& event) = default;

	/// Move constructor
	/// \param event Event to copy from
	input_keyboard(input_keyboard&& event) = default;

	/// Copy assignment
	/// \param event The event to copy from
	/// \return *this after the copy
	input_keyboard& operator=(const input_keyboard& event) = default;

	/// Move assignment
	/// \param event Event to move from
	/// \return *this after the move
	input_keyboard& operator=(input_keyboard&& event) = default;

	/// Destructor
	~input_keyboard() = default;

	/// The key that was pressed
	key m_input_key;

	/// True for pressed, false for released
	bool m_pressed;

	/// The state of the modifiers
	int m_modifier_state;

	/// Equality comparision
	bool operator==(const input_keyboard& other) const
	{
		return this->m_input_key == other.m_input_key && this->m_pressed == other.m_pressed;
	}

	/// Inequality comparision
	bool operator!=(const input_keyboard& other) const { return !(*this == other); }
};

/// A mouse button
enum class mouse_button {
	e_left_button,
	e_right_button,
	e_middle_button,
	e_button_1,
	e_button_2,
};

/// A input event from moving the mouse
struct input_mouse_move {
	/// Default constructor
	input_mouse_move() = default;

	/// Copy constructor
	/// \param event Event to copy from
	input_mouse_move(const input_mouse_move& event) = default;

	/// Move constructor
	/// \param event Event to move from
	input_mouse_move(input_mouse_move&& event) = default;

	/// Copy assignment
	/// \param event Event to copy from
	/// \return *this after copy
	input_mouse_move& operator=(const input_mouse_move& event) = default;

	/// Move assignment
	/// \param event Event to move from
	/// \return *this after move
	input_mouse_move& operator=(input_mouse_move&& event) = default;

	/// Destructor
	~input_mouse_move() = default;

	/// The new location of the mouse
	glm::vec2 m_new_location;

	/// The current state of the keyboard modifiers
	int m_modifier_state;

	/// Comparision operator
	bool operator==(const input_mouse_move& other) const
	{
		return m_new_location == other.m_new_location;
	}

	/// Inequality operator
	bool operator!=(const input_mouse_move& other) const { return !(*this == other); }
};

/// An input event from pressing a mouse button
struct input_mouse_button {
	/// Default constructor
	input_mouse_button() = default;

	/// Copy constructor
	/// \param event Event to copy from
	input_mouse_button(const input_mouse_button& event) = default;

	/// Move constructor
	/// \param event Event to move from
	input_mouse_button(input_mouse_button&& event) = default;

	/// Copy assignment
	/// \param event Event to copy from
	/// \return *this after copy
	input_mouse_button& operator=(const input_mouse_button& event) = default;

	/// Move assignment
	/// \param event Event to move from
	/// \return *this after move
	input_mouse_button& operator=(input_mouse_button&& event) = default;

	/// Destructor
	~input_mouse_button() = default;

	/// The button that was pressed
	mouse_button m_button;

	/// If the mouse button was pressed, true for pressed false for released
	bool m_pressed;

	/// The current keyboard modifier state
	int m_modifier_state;

	/// The location on the viewport that the action occured
	glm::uvec2 m_location;

	/// Comparision operator
	bool operator==(const input_mouse_button& other) const
	{
		return m_button == other.m_button && m_pressed == other.m_pressed;
	}

	/// Inequality operator
	bool operator!=(const input_mouse_button& other) const { return !(*this == other); }
};

/// An input event from scrolling the scroll wheel
struct input_scroll_wheel {
	/// Default constructor
	input_scroll_wheel() = default;

	/// Copy consructor
	/// \param event Event to copy from
	input_scroll_wheel(const input_scroll_wheel& event) = default;

	/// Move consturctor
	/// \param event Event to move from
	input_scroll_wheel(input_scroll_wheel&& event) = default;

	/// Copy assignment
	/// \param event Event to copy from
	/// \return *this after copy
	input_scroll_wheel& operator=(const input_scroll_wheel& event) = default;

	/// Move assignment
	/// \param event Event to move from
	/// \return *this after move
	input_scroll_wheel& operator=(input_scroll_wheel&& event) = default;

	/// Desturctor
	~input_scroll_wheel() = default;

	/// The amount that the user scrolled
	/// for x, right is positive
	/// for y, away from user is positive
	glm::vec2 amount;

	/// The state of the keyboard modifiers
	int m_modifier_state;

	/// Comparision operator
	bool operator==(const input_scroll_wheel& other) const { return amount == other.amount; }
	/// Inequality operator
	bool operator!=(const input_scroll_wheel& other) const { return !(*this == other); }
};

using input_event =
	boost::variant<input_keyboard, input_mouse_move, input_mouse_button, input_scroll_wheel>;
}

#endif  // GE_INPUT_EVENT_HPP
