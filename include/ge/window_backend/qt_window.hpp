#pragma once

#include "ge/concept/window.hpp"
#include "ge/application.hpp"

#include <glm/glm.hpp>

#include <boost/optional.hpp>

#include <boost/signals2.hpp>

#include <QMainWindow>

namespace ge {
namespace window_backend {

class qt;

class qt_window : public QMainWindow
{
public:
	qt& qt_inst;
	
	qt_window(qt& app, const char* title, boost::optional<glm::uvec2> loc, glm::uvec2 size, bool fullscreen, bool decorated);
	
	// can't really copy OpenGL context, so don't allow copying of windows
	qt_window(const qt_window&) = delete;
	
	// move constructor
	qt_window(qt_window&& other) = default;
	
	// again, can't copy a context, no copy operator
	qt_window& operator=(const qt_window&) = delete;
	
	// move operator
	qt_window& operator=(qt_window&& other)
	{
		
		return *this;
	}
	
	~qt_window();
	
	// checking if it is valid
	operator bool() const
	{
	}
	
	void set_title(const char* new_title)
	{
		// TODO: implemtn
	}
	
	std::string get_title() const
	{
		// TODO: implement
	}
	
	void set_size(glm::uvec2 new_size)
	{
		setFixedSize(new_size.x, new_size.y);
	}
	glm::uvec2 get_size() const
	{
		return {width(), height()};
	}
	
	boost::signals2::signal<void()> sig_quit;
	
	
	

};
BOOST_CONCEPT_ASSERT((ge::concept::Window<qt_window>));
	

} // namespace window_backend
} // namespace ge
