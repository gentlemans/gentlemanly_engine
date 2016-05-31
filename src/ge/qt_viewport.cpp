#include "ge/gl.hpp"
#include "ge/qt_viewport.hpp"
#include "ge/camera_component.hpp"
#include "ge/model_system.hpp"
#include "ge/qt_application.hpp"
#include "ge/qt_window.hpp"

#include "ge/ortho2d.hpp"


#include <chrono>
#include <iostream>
#include <stdexcept>

#include <QSurface>
#include <QSurfaceFormat>
#include <QKeyEvent>

#include <glm/gtx/matrix_transform_2d.hpp>

namespace ge
{
qt_viewport::qt_viewport(qt_application& backend, qt_window& window)
	: QOpenGLWidget(&window), m_window(&window)
{
	window.setCentralWidget(this);

	QSurfaceFormat format;
	format.setDepthBufferSize(24);
	format.setVersion(3, 3);
	format.setProfile(QSurfaceFormat::CoreProfile);
	setFormat(format);
}

void qt_viewport::initializeGL() { m_window->qt_inst.signal_init(); }
void qt_viewport::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	static auto last_tick = std::chrono::system_clock::now();
	auto now = std::chrono::system_clock::now();

	std::chrono::duration<float> diff = now - last_tick;

	last_tick = now;

	m_window->qt_inst.signal_update(diff.count());

	update();
}

void qt_viewport::resizeGL(int w, int h) {}
void qt_viewport::set_background_color(const glm::vec4 newColor)
{
	glClearColor(newColor.r, newColor.g, newColor.b, newColor.a);
}

key qt_key_to_ge_key(Qt::Key k) {
	switch (k) {
		case Qt::Key_Escape: return key::e_escape;
		case Qt::Key_Tab: return key::e_tab;
		case Qt::Key_Backspace: return key::e_backspace;
		case Qt::Key_Return: return key::e_return;
		case Qt::Key_Enter: return key::e_numpad_enter;
		case Qt::Key_Insert: return key::e_insert;
		case Qt::Key_Delete: return key::e_delete;
		case Qt::Key_Pause: return key::e_pause;
		case Qt::Key_Print: return key::e_print_screen;
		case Qt::Key_Home: return key::e_home;
		case Qt::Key_End: return key::e_end;
		case Qt::Key_Left: return key::e_left;
		case Qt::Key_Up: return key::e_up;
		case Qt::Key_Right: return key::e_right;
		case Qt::Key_Down: return key::e_down;
		case Qt::Key_PageUp: return key::e_page_up;
		case Qt::Key_PageDown: return key::e_page_down;
		case Qt::Key_Shift: return key::e_left_shift;
		case Qt::Key_Control: return key::e_left_ctrl;
		case Qt::Key_Meta: return key::e_left_meta;
		case Qt::Key_Alt: return key::e_left_alt;
		case Qt::Key_CapsLock: return key::e_caps_lock;
		case Qt::Key_NumLock: return key::e_num_lock;
		case Qt::Key_ScrollLock: return key::e_scroll_lock;
		case Qt::Key_F1: return key::e_F1;
		case Qt::Key_F2: return key::e_F2;
		case Qt::Key_F3: return key::e_F3;
		case Qt::Key_F4: return key::e_F4;
		case Qt::Key_F5: return key::e_F5;
		case Qt::Key_F6: return key::e_F6;
		case Qt::Key_F7: return key::e_F7;
		case Qt::Key_F8: return key::e_F8;
		case Qt::Key_F9: return key::e_F9;
		case Qt::Key_F10: return key::e_F10;
		case Qt::Key_F11: return key::e_F11;
		case Qt::Key_F12: return key::e_F12;
		case Qt::Key_Space: return key::e_space;
		case Qt::Key_Comma: return key::e_comma;
		case Qt::Key_Minus: return key::e_minus;
		case Qt::Key_Period: return key::e_period;
		case Qt::Key_Slash: return key::e_forward_slash;
		case Qt::Key_0: return key::e_0;
		case Qt::Key_1: return key::e_1;
		case Qt::Key_2: return key::e_2;
		case Qt::Key_3: return key::e_3;
		case Qt::Key_4: return key::e_4;
		case Qt::Key_5: return key::e_5;
		case Qt::Key_6: return key::e_6;
		case Qt::Key_7: return key::e_7;
		case Qt::Key_8: return key::e_8;
		case Qt::Key_9: return key::e_9;
		case Qt::Key_Semicolon: return key::e_semicolon;
		case Qt::Key_A: return key::e_a;
		case Qt::Key_B: return key::e_b;
		case Qt::Key_C: return key::e_c;
		case Qt::Key_D: return key::e_d;
		case Qt::Key_E: return key::e_e;
		case Qt::Key_F: return key::e_f;
		case Qt::Key_G: return key::e_g;
		case Qt::Key_H: return key::e_h;
		case Qt::Key_I: return key::e_i;
		case Qt::Key_J: return key::e_j;
		case Qt::Key_K: return key::e_k;
		case Qt::Key_L: return key::e_l;
		case Qt::Key_M: return key::e_m;
		case Qt::Key_N: return key::e_n;
		case Qt::Key_O: return key::e_o;
		case Qt::Key_P: return key::e_p;
		case Qt::Key_Q: return key::e_q;
		case Qt::Key_R: return key::e_r;
		case Qt::Key_S: return key::e_s;
		case Qt::Key_T: return key::e_t;
		case Qt::Key_U: return key::e_u;
		case Qt::Key_V: return key::e_v;
		case Qt::Key_W: return key::e_w;
		case Qt::Key_X: return key::e_x;
		case Qt::Key_Y: return key::e_y;
		case Qt::Key_Z: return key::e_z;
		case Qt::Key_BracketLeft: return key::e_left_bracket;
		case Qt::Key_Backslash: return key::e_backward_slash;
		case Qt::Key_BracketRight: return key::e_right_bracket;

	}
	
}

bool qt_viewport::event(QEvent* event) {
	
	switch(event->type()) {
		case QEvent::Type::MouseButtonPress: {
			auto ev_cast = static_cast<QMouseEvent*>(event);
			
			switch(ev_cast->button()) {
				case Qt::LeftButton: events.push_back(input_mouse_button{mouse_button::e_left_button, true}); break;
				case Qt::RightButton: events.push_back(input_mouse_button{mouse_button::e_right_button, true}); break;
				case Qt::MiddleButton: events.push_back(input_mouse_button{mouse_button::e_middle_button, true}); break;
			}
			return true;
		}
		break;
		case QEvent::Type::MouseButtonRelease: {

			auto ev_cast = static_cast<QMouseEvent*>(event);
			
			switch(ev_cast->button()) {
				case Qt::LeftButton: events.push_back(input_mouse_button{mouse_button::e_left_button, false}); break;
				case Qt::RightButton: events.push_back(input_mouse_button{mouse_button::e_right_button, false}); break;
				case Qt::MiddleButton: events.push_back(input_mouse_button{mouse_button::e_middle_button, false}); break;
			}
			return true;
		}
		case QEvent::Type::KeyPress: {
			
			auto ev_cast = static_cast<QKeyEvent*>(event);
			
			events.push_back(input_keyboard{qt_key_to_ge_key((Qt::Key)ev_cast->key()), true});
			
		}
		break;
		case QEvent::Type::KeyRelease: {
			
			auto ev_cast = static_cast<QKeyEvent*>(event);
			
			events.push_back(input_keyboard{qt_key_to_ge_key((Qt::Key)ev_cast->key()), false});

		}
		break;
		case QEvent::Type::MouseMove: {
			auto ev_cast = static_cast<QMouseEvent*>(event);
			
			events.push_back(input_mouse_move{{ev_cast->x(), ev_cast->y()}});
			
		}
		break;
	}
}
	


input_event qt_viewport::get_next_input_event() {
	
	auto cpy = *events.begin();
	events.pop_front();

	return cpy;
}

}  // namespace ge
