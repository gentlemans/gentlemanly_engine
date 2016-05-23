#include "ge/qt_window.hpp"
#include "ge/qt_application.hpp"

namespace ge
{
qt_window::qt_window(qt_application& app, const char* title, boost::optional<glm::uvec2> loc,
	glm::uvec2 size, bool fullscreen, bool decorated)
	: qt_inst(app)
{
	setWindowTitle(QLatin1String(title));

	setFixedSize(size.x, size.y);

	if (fullscreen) showFullScreen();
	if (!decorated) setWindowFlags(Qt::CustomizeWindowHint);

	show();

	connect(&qt_inst.qt_app, &QApplication::aboutToQuit, [this] { qt_inst.signal_quit(); });
}

qt_window::~qt_window() {}
}  // namespace ge
