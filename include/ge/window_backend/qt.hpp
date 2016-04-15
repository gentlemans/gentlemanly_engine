#pragma once

#include "ge/window_backend/qt_window.hpp"
#include "ge/window_backend/qt_viewport.hpp"

#include <QApplication>

#include <memory>
namespace ge
{
namespace window_backend
{
class qt
{
public:
	application<qt>& app;
	QApplication qt_app;
	using window = qt_window;
	using viewport = qt_viewport;

	qt(application<qt>& _app, int& argc, char** argv);

	qt(const qt&) = delete;

	std::unique_ptr<window> make_window(const char* title, boost::optional<glm::uvec2> loc,
										glm::uvec2 size, bool fullscreen, bool decorated)
	{
		return std::make_unique<window>(*this, title, loc, size, fullscreen, decorated);
	}

	std::unique_ptr<viewport> make_viewport(window& window)
	{
		return std::make_unique<viewport>(*this, window);
	}

	void execute();
};

}  // namespace window_backend
}  // namespace ge
