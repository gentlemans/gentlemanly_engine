#pragma once

#include "ge/qt_window.hpp"
#include "ge/qt_viewport.hpp"

#include "ge/concept/application.hpp"

#include <boost/signals2.hpp>

#include <QApplication>

#include <memory>
namespace ge
{
class qt_application
{
public:
	QApplication qt_app;
	using window = qt_window;
	using viewport = qt_viewport;

	qt_application(int& argc, char** argv);

	qt_application(const qt_application&) = delete;

	std::unique_ptr<window> make_window(const char* title, boost::optional<glm::uvec2> loc,
		glm::uvec2 size, bool fullscreen, bool decorated)
	{
		return std::make_unique<window>(*this, title, loc, size, fullscreen, decorated);
	}

	std::unique_ptr<viewport> make_viewport(window& window)
	{
		return std::make_unique<viewport>(*this, window);
	}

	boost::signals2::signal<void(float)> signal_update;
	boost::signals2::signal<void()> signal_init;

	void execute();
};

}  // namespace ge
