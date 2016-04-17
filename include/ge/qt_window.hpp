#pragma once

#include "ge/concept/window.hpp"

#include <glm/glm.hpp>

#include <boost/optional.hpp>

#include <boost/signals2.hpp>

#include <QMainWindow>

namespace ge
{
class qt_application;

class qt_window : public QMainWindow
{
public:
	qt_application& qt_inst;

	qt_window(qt_application& app, const char* title, boost::optional<glm::uvec2> loc, glm::uvec2 size,
		bool fullscreen, bool decorated);

	// can't really copy OpenGL context, so don't allow copying of windows
	qt_window(const qt_window&) = delete;

	// move constructor
	qt_window(qt_window&& other) = default;

	// again, can't copy a context, no copy operator
	qt_window& operator=(const qt_window&) = delete;

	// move operator
	qt_window& operator=(qt_window&& other) { return *this; }
	~qt_window();

	void set_title(const char* new_title) { setWindowTitle(new_title); }
	std::string get_title() const { return windowTitle().toStdString(); }
	void set_size(glm::uvec2 new_size) { setFixedSize(new_size.x, new_size.y); }
	glm::uvec2 get_size() const { return {width(), height()}; }
	boost::signals2::signal<void()> sig_quit;
};
BOOST_CONCEPT_ASSERT((ge::concept::Window<qt_window>));

}  // namespace ge
