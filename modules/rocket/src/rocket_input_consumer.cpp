#include "ge/rocket_input_consumer.hpp"

using namespace ge;

Rocket::Core::Input::KeyIdentifier ge_to_rocket_key(key k)
{
	using namespace Rocket::Core::Input;

	switch (k) {
	case key::e_left_shift: return KI_LSHIFT;
	case key::e_right_shift: return KI_RSHIFT;
	case key::e_left_meta: return KI_LMETA;
	case key::e_right_meta: return KI_RMETA;
	case key::e_left_alt: return KI_LMENU;
	case key::e_right_alt: return KI_RMENU;
	case key::e_left_ctrl: return KI_LCONTROL;
	case key::e_right_ctrl: return KI_RCONTROL;
	case key::e_minus: return KI_OEM_MINUS;
	case key::e_equals: return KI_OEM_PLUS;
	case key::e_a: return KI_A;
	case key::e_b: return KI_B;
	case key::e_c: return KI_C;
	case key::e_d: return KI_D;
	case key::e_e: return KI_E;
	case key::e_f: return KI_F;
	case key::e_g: return KI_G;
	case key::e_h: return KI_H;
	case key::e_i: return KI_I;
	case key::e_j: return KI_J;
	case key::e_k: return KI_K;
	case key::e_l: return KI_L;
	case key::e_m: return KI_M;
	case key::e_n: return KI_N;
	case key::e_o: return KI_O;
	case key::e_p: return KI_P;
	case key::e_q: return KI_Q;
	case key::e_r: return KI_R;
	case key::e_s: return KI_S;
	case key::e_t: return KI_T;
	case key::e_u: return KI_U;
	case key::e_v: return KI_V;
	case key::e_w: return KI_W;
	case key::e_x: return KI_X;
	case key::e_y: return KI_Y;
	case key::e_z: return KI_Z;
	case key::e_0: return KI_0;
	case key::e_1: return KI_1;
	case key::e_2: return KI_2;
	case key::e_3: return KI_3;
	case key::e_4: return KI_4;
	case key::e_5: return KI_5;
	case key::e_6: return KI_6;
	case key::e_7: return KI_7;
	case key::e_8: return KI_8;
	case key::e_9: return KI_9;
	case key::e_comma: return KI_OEM_COMMA;
	case key::e_period: return KI_OEM_PERIOD;
	case key::e_forward_slash: return KI_OEM_2;
	case key::e_backward_slash: return KI_OEM_5;
	case key::e_backspace: return KI_BACK;
	case key::e_return: return KI_RETURN;
	case key::e_semicolon: return KI_OEM_1;
	case key::e_apostrophe: return KI_OEM_7;
	case key::e_back_tick: return KI_OEM_3;
	case key::e_space: return KI_SPACE;
	case key::e_escape: return KI_ESCAPE;
	case key::e_insert: return KI_INSERT;
	case key::e_delete: return KI_DELETE;
	case key::e_home: return KI_HOME;
	case key::e_end: return KI_END;
	case key::e_page_up: return KI_PRIOR;
	case key::e_page_down: return KI_NEXT;
	case key::e_print_screen: return KI_SNAPSHOT;
	case key::e_scroll_lock: return KI_SCROLL;
	case key::e_pause: return KI_PAUSE;
	case key::e_left_bracket: return KI_OEM_4;
	case key::e_right_bracket: return KI_OEM_6;
	case key::e_tab: return KI_TAB;
	case key::e_caps_lock: return KI_CAPITAL;
	case key::e_F1: return KI_F1;
	case key::e_F2: return KI_F2;
	case key::e_F3: return KI_F3;
	case key::e_F4: return KI_F4;
	case key::e_F5: return KI_F5;
	case key::e_F6: return KI_F6;
	case key::e_F7: return KI_F7;
	case key::e_F8: return KI_F8;
	case key::e_F9: return KI_F9;
	case key::e_F10: return KI_F10;
	case key::e_F11: return KI_F11;
	case key::e_F12: return KI_F12;
	case key::e_numpad_0: return KI_NUMPAD0;
	case key::e_numpad_1: return KI_NUMPAD1;
	case key::e_numpad_2: return KI_NUMPAD2;
	case key::e_numpad_3: return KI_NUMPAD3;
	case key::e_numpad_4: return KI_NUMPAD4;
	case key::e_numpad_5: return KI_NUMPAD5;
	case key::e_numpad_6: return KI_NUMPAD6;
	case key::e_numpad_7: return KI_NUMPAD7;
	case key::e_numpad_8: return KI_NUMPAD8;
	case key::e_numpad_9: return KI_NUMPAD9;
	case key::e_numpad_divide: return KI_DIVIDE;
	case key::e_numpad_times: return KI_MULTIPLY;
	case key::e_numpad_minus: return KI_SUBTRACT;
	case key::e_numpad_plus: return KI_ADD;
	case key::e_numpad_enter: return KI_NUMPADENTER;
	case key::e_numpad_period: return KI_SEPARATOR;
	case key::e_left: return KI_LEFT;
	case key::e_up: return KI_UP;
	case key::e_down: return KI_DOWN;
	case key::e_right: return KI_RIGHT;
	}
	return KI_UNKNOWN;
}

Rocket::Core::Input::KeyModifier ge_mods_to_rocket(int mod)
{
	int ret = 0;

	using namespace Rocket::Core::Input;

	if (mod & key_modifier::e_left_shift) ret |= KM_SHIFT;
	if (mod & key_modifier::e_right_shift) ret |= KM_SHIFT;
	if (mod & key_modifier::e_left_ctrl) ret |= KM_CTRL;
	if (mod & key_modifier::e_right_ctrl) ret |= KM_CTRL;
	if (mod & key_modifier::e_left_alt) ret |= KM_ALT;
	if (mod & key_modifier::e_right_alt) ret |= KM_ALT;
	if (mod & key_modifier::e_left_gui) ret |= KM_META;
	if (mod & key_modifier::e_right_gui) ret |= KM_META;
	if (mod & key_modifier::e_num_lock) ret |= KM_NUMLOCK;
	if (mod & key_modifier::e_caps_lock) ret |= KM_CAPSLOCK;

	return (KeyModifier)ret;
}

int ge_mb_to_rocket(mouse_button mb)
{
	switch (mb) {
	case mouse_button::e_left_button: return 0;
	case mouse_button::e_right_button: return 1;
	case mouse_button::e_middle_button: return 2;
	case mouse_button::e_button_1: return 3;
	case mouse_button::e_button_2: return 4;
	}
	return 0;
}

struct input_passer_visitor : boost::static_visitor<void> {
	input_passer_visitor(Rocket::Core::Context* arg_cont) : context{arg_cont} {}
	void operator()(input_keyboard k)
	{
		if (k.m_pressed) {
			context->ProcessKeyDown(
				ge_to_rocket_key(k.m_input_key), ge_mods_to_rocket(k.m_modifier_state));
		} else {
			context->ProcessKeyUp(
				ge_to_rocket_key(k.m_input_key), ge_mods_to_rocket(k.m_modifier_state));
		}
	}

	void operator()(input_mouse_button mb)
	{
		if (mb.m_pressed) {
			context->ProcessMouseButtonDown(
				ge_mb_to_rocket(mb.m_button), ge_mods_to_rocket(mb.m_modifier_state));
		} else {
			context->ProcessMouseButtonUp(
				ge_mb_to_rocket(mb.m_button), ge_mods_to_rocket(mb.m_modifier_state));
		}
	}

	void operator()(input_mouse_move mm)
	{
		context->ProcessMouseMove(
			int(mm.m_new_location.x), int(mm.m_new_location.y), ge_mods_to_rocket(mm.m_modifier_state));
	}

	void operator()(input_scroll_wheel sw)
	{
		context->ProcessMouseWheel(int(sw.amount.y), ge_mods_to_rocket(sw.m_modifier_state));
	}

	Rocket::Core::Context* context;
};

void rocket_input_consumer::handle_input(const input_event& event)
{
	auto visitor = input_passer_visitor{m_context};

	event.apply_visitor(visitor);
}
